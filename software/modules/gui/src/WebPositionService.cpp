
#include "WebPositionService.h"

#include <iostream>
#include <thread>

#include "robot.pb.h"

const int INTERVAL_SENDING_POSITION_REFRESH_MS = 20;

void WebPositionService::registerWebServerRequestListener(
    const std::weak_ptr<IWebServerRequestListener> &webserver_listener) {
    webserver_listeners_.push_back(webserver_listener);
}

void WebPositionService::publishToWebServerPositionRequestListeners(
    const double &pos_x,
    const double &pos_y,
    const double &orientation) const {
    for (auto const &webserver_listener_ptr : webserver_listeners_) {
        if (auto webserver_listener = webserver_listener_ptr.lock()) {
            webserver_listener->onWebServerPositionRequest(pos_x, pos_y, orientation);
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
    publishToWebServerPositionRequestListeners(
        request->pos_x_m(),
        request->pos_y_m(),
        request->orientation_rad());

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
        position_orientation_request.set_pos_x_m(pos_x_m_);
        position_orientation_request.set_pos_y_m(pos_y_m_);
        position_orientation_request.set_orientation_rad(orientation_rad_);

        writer->Write(position_orientation_request);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(INTERVAL_SENDING_POSITION_REFRESH_MS));
    }
    return ::grpc::Status::OK;
}

void WebPositionService::setPosition(
    const double &pos_x_m,
    const double &pos_y_m,
    const double &orientation_rad) {
    pos_x_m_ = pos_x_m;
    pos_y_m_ = pos_y_m;
    orientation_rad_ = orientation_rad;
}

void WebPositionService::setSpeed(const int &motor1, const int &motor2) const {
    std::cout << motor1 << " " << motor2 << std::endl;
    publishToWebServerSpeedRequestListeners(motor1, motor2);
}