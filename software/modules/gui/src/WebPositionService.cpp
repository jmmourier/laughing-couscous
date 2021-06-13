
#include "WebPositionService.h"

#include <iostream>
#include <thread>

#include "PositionOrientation.h"
#include "RobotState.h"
#include "Types.h"
#include "robot.pb.h"

const int INTERVAL_SENDING_POSITION_REFRESH_MS = 20;

WebPositionService::WebPositionService()
    : robot_state_(RobotState(PositionOrientation(0, 0, 0), 0, true, 0, 0, ActionType::WAIT)) {}

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
        robot_data_request.set_pos_x_m(robot_state_.position_orientation_.x_m_);
        robot_data_request.set_pos_y_m(robot_state_.position_orientation_.y_m_);
        robot_data_request.set_orientation_rad(robot_state_.position_orientation_.orientation_rad_);
        robot_data_request.set_is_grabber_open(robot_state_.is_grabber_open_);
        robot_data_request.set_mission_started_at(robot_state_.mission_started_at_);
        robot_data_request.set_mission_ended_at(robot_state_.mission_ended_at_);

        web_service::ActionType action_type = web_service::ActionType::UNKNOWN;

        switch (robot_state_.current_action_) {
            case ActionType::WAIT:
                action_type = web_service::ActionType::WAIT;
                break;
            case ActionType::GRABBER:
                action_type = web_service::ActionType::GRABBER;
                break;
            case ActionType::MOVE:
                action_type = web_service::ActionType::MOVE;
                break;
            case ActionType::MOVE_BACKWARD:
                action_type = web_service::ActionType::MOVE_BACKWARD;
                break;
            case ActionType::TURN:
                action_type = web_service::ActionType::TURN;
                break;
            case ActionType::UNKNOWN:
                action_type = web_service::ActionType::UNKNOWN;
                break;
        }

        robot_data_request.set_action_type(action_type);

        writer->Write(robot_data_request);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(INTERVAL_SENDING_POSITION_REFRESH_MS));
    }
    return ::grpc::Status::OK;
};

void WebPositionService::setRobotState(const RobotState &robot_state) {
    robot_state_ = robot_state;
}

RobotState WebPositionService::getRobotState() {
    return robot_state_;
}