#ifndef WEB_POSITION_SERVICE_H
#define WEB_POSITION_SERVICE_H

#include "robot.grpc.pb.h"

class WebPositionService final : public web_service::Position::Service {
   public:
    explicit WebPositionService(
        std::function<void(double pos_x_m, double pos_y_m, double orientation_rad)>
            on_set_position_callback,
        std::function<void(int motor1, int motor2)> on_set_speed_callback);

    ::grpc::Status setSpeed(
        ::grpc::ServerContext *context,
        const ::web_service::SpeedMsg *request,
        ::web_service::Empty *response) override;

    ::grpc::Status onAbsolutePositionUpdated(
        ::grpc::ServerContext *context,
        const ::web_service::Empty *request,
        ::grpc::ServerWriter<::web_service::PositionMsg> *writer) override;

    ::grpc::Status setAbsolutePosition(
        ::grpc::ServerContext *context,
        const ::web_service::PositionMsg *request,
        ::web_service::Empty *response) override;

    void updatePosition(double pos_x_m, double pos_y_m, double orientation_rad);

   private:
    const std::function<void(double pos_x_m, double pos_y_m, double orientation_rad)>
        on_set_position_callback_;
    const std::function<void(int motor1, int motor2)> on_set_speed_callback_;

    double pos_x_m_;
    double pos_y_m_;
    double orientation_rad_;
};

#endif  // WEB_POSITION_SERVICE_H