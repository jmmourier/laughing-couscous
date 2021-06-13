
#include "WebPositionService.h"

#include <iostream>
#include <thread>

#include "PositionOrientation.h"
#include "robot.pb.h"

const int INTERVAL_SENDING_POSITION_REFRESH_MS = 20;

WebPositionService::WebPositionService()
    : position_orientation_(PositionOrientation(0, 0, 0)),
      battery_v_(0),
      is_grabber_open_(true),
      mission_started_at_(0),
      mission_ended_at_(0) {}

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

void WebPositionService::publishToWebServerTargetOrientationListeners(
    const float &orientation_rad) {
    for (auto const &webserver_listener_ptr : webserver_listeners_) {
        if (auto webserver_listener = webserver_listener_ptr.lock()) {
            webserver_listener->onWebServerTargetOrientationRequest(orientation_rad);
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
    const ::web_service::RobotDataRequest *request,
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

::grpc::Status WebPositionService::setTargetOrientationRequest(
    ::grpc::ServerContext *context,
    const ::web_service::OrientationRequest *request,
    ::web_service::Empty *response) {
    publishToWebServerTargetOrientationListeners(request->orientation_rad());

    return ::grpc::Status::OK;
}

::grpc::Status WebPositionService::registerRobotDataObserver(
    ::grpc::ServerContext *context,
    const ::web_service::Empty *request,
    ::grpc::ServerWriter<::web_service::RobotDataRequest> *writer) {
    web_service::RobotDataRequest robot_data_request;

    while (true) {
        robot_data_request.set_pos_x_m(position_orientation_.x_m_);
        robot_data_request.set_pos_y_m(position_orientation_.y_m_);
        robot_data_request.set_orientation_rad(position_orientation_.orientation_rad_);
        robot_data_request.set_is_grabber_open(is_grabber_open_);
        robot_data_request.set_mission_started_at(mission_started_at_);
        robot_data_request.set_mission_ended_at(mission_ended_at_);

        writer->Write(robot_data_request);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(INTERVAL_SENDING_POSITION_REFRESH_MS));
    }
    return ::grpc::Status::OK;
};

void WebPositionService::setPosition(const PositionOrientation &position_orientation) {
    position_orientation_ = position_orientation;
}

void WebPositionService::setSpeed(const int &motor1, const int &motor2) const {
    std::cout << motor1 << " " << motor2 << std::endl;
    publishToWebServerSpeedRequestListeners(motor1, motor2);
}

void WebPositionService::setBattery(const float &battery_v) {
    battery_v_ = battery_v;
}

void WebPositionService::setGrabberState(const bool &is_grabber_open) {
    is_grabber_open_ = is_grabber_open;
}

void WebPositionService::setMissionStartedAt(const long &mission_started_at) {
    mission_started_at_ = mission_started_at;
}

void WebPositionService::setMissionEndedAt(const long &mission_ended_at) {
    mission_ended_at_ = mission_ended_at;
}