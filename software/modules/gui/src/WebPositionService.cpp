
#include "WebPositionService.h"

#include <iostream>
#include <thread>

#include "PositionOrientation.h"
#include "robot.pb.h"

const int INTERVAL_SENDING_POSITION_REFRESH_MS = 20;

WebPositionService::WebPositionService() : position_orientation_(PositionOrientation(0, 0, 0)) {}

void WebPositionService::registerWebServerRequestListener(
    const std::weak_ptr<IWebServerRequestListener> &webserver_listener) {
    webserver_listeners_.push_back(webserver_listener);
}

void WebPositionService::publishToWebServerPositionRequestListeners(
    const PositionOrientation &position_orientation) const {
    for (auto const &webserver_listener_ptr : webserver_listeners_) {
        if (auto webserver_listener = webserver_listener_ptr.lock()) {
            webserver_listener->onWebServerPositionRequest(position_orientation);
        }
    }
}
void WebPositionService::publishToWebServerSpeedRequestListeners(
    const int &motor1,
    const int &motor2) const {
    for (auto const &webserver_listener_ptr : webserver_listeners_) {
        if (auto webserver_listener = webserver_listener_ptr.lock()) {
            webserver_listener->onWebServerSpeedRequest(motor1, motor2);
        }
    }
}

void WebPositionService::publishToWebServerTargetPositionListeners(
    const double &pos_x,
    const double &pos_y) {
    for (auto const &webserver_listener_ptr : webserver_listeners_) {
        if (auto webserver_listener = webserver_listener_ptr.lock()) {
            webserver_listener->onWebServerTargetPositionRequest(pos_x, pos_y);
        }
    }
}

::grpc::Status WebPositionService::setSpeedRequest(
    ::grpc::ServerContext *context,
    const ::web_service::SpeedRequest *request,
    ::web_service::Empty *response) {
    publishToWebServerSpeedRequestListeners(request->motor1(), request->motor2());

    return ::grpc::Status::OK;
};

::grpc::Status WebPositionService::setAbsolutePositionRequest(
    ::grpc::ServerContext *context,
    const ::web_service::PositionOrientationRequest *request,
    ::web_service::Empty *response) {
    const PositionOrientation position_orientation(
        request->pos_x_m(),
        request->pos_y_m(),
        request->orientation_rad());

    publishToWebServerPositionRequestListeners(position_orientation);

    return ::grpc::Status::OK;
}

::grpc::Status WebPositionService::setTargetPositionRequest(
    ::grpc::ServerContext *context,
    const ::web_service::PositionRequest *request,
    ::web_service::Empty *response) {
    publishToWebServerTargetPositionListeners(request->pos_x_m(), request->pos_y_m());

    return ::grpc::Status::OK;
};

::grpc::Status WebPositionService::registerPositionObserver(
    ::grpc::ServerContext *context,
    const ::web_service::Empty *request,
    ::grpc::ServerWriter<::web_service::PositionOrientationRequest> *writer) {
    web_service::PositionOrientationRequest position_orientation_request;

    while (true) {
        position_orientation_request.set_pos_x_m(position_orientation_.x_m_);
        position_orientation_request.set_pos_y_m(position_orientation_.y_m_);
        position_orientation_request.set_orientation_rad(position_orientation_.orientation_rad_);

        writer->Write(position_orientation_request);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(INTERVAL_SENDING_POSITION_REFRESH_MS));
    }
    return ::grpc::Status::OK;
}

void WebPositionService::setPosition(const PositionOrientation &position_orientation) {
    position_orientation_ = position_orientation;
}

void WebPositionService::setSpeed(const int &motor1, const int &motor2) const {
    std::cout << motor1 << " " << motor2 << std::endl;
    publishToWebServerSpeedRequestListeners(motor1, motor2);
}