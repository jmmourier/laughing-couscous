
#include "WebPositionService.h"

#include <thread>

#include "robot.pb.h"

const int INTERVAL_SENDING_POSITION_REFRESH_MS = 20;

WebPositionService::WebPositionService(
    std::function<void(double pos_x_m, double pos_y_m, double orientation_rad)>
        on_set_position_callback,
    std::function<void(int motor1, int motor2)> on_set_speed_callback)
    : web_service::Position::Service(),
      on_set_position_callback_(std::move(on_set_position_callback)),
      on_set_speed_callback_(std::move(on_set_speed_callback)),
      pos_x_m_(0),
      pos_y_m_(0),
      orientation_rad_(0) {}

::grpc::Status WebPositionService::setSpeed(
    ::grpc::ServerContext *context,
    const ::web_service::SpeedMsg *request,
    ::web_service::Empty *response) {
    on_set_speed_callback_(request->motor1(), request->motor2());

    return ::grpc::Status::OK;
};

::grpc::Status WebPositionService::setAbsolutePosition(
    ::grpc::ServerContext *context,
    const ::web_service::PositionMsg *request,
    ::web_service::Empty *response) {
    on_set_position_callback_(request->pos_x_m(), request->pos_y_m(), request->orientation_rad());

    return ::grpc::Status::OK;
}

::grpc::Status WebPositionService::onAbsolutePositionUpdated(
    ::grpc::ServerContext *context,
    const ::web_service::Empty *request,
    ::grpc::ServerWriter<::web_service::PositionMsg> *writer) {
    web_service::PositionMsg position_msg;

    while (true) {
        position_msg.set_pos_x_m(pos_x_m_);
        position_msg.set_pos_y_m(pos_y_m_);
        position_msg.set_orientation_rad(orientation_rad_);

        writer->Write(position_msg);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(INTERVAL_SENDING_POSITION_REFRESH_MS));
    }
    return ::grpc::Status::OK;
}

void WebPositionService::updatePosition(double pos_x_m, double pos_y_m, double orientation_rad) {
    pos_x_m_ = pos_x_m;
    pos_y_m_ = pos_y_m;
    orientation_rad_ = orientation_rad;
}