#ifndef WEB_POSITION_SERVICE_H
#define WEB_POSITION_SERVICE_H

#include "robot.grpc.pb.h"

class WebPositionService final : public web_service::Position::Service {
   public:
    explicit WebPositionService(
        std::function<void(double pos_x_m, double pos_y_m, double orientation_rad)>
            on_set_position_callback);

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

    double pos_x_m_;
    double pos_y_m_;
    double orientation_rad_;
};

#endif  // WEB_POSITION_SERVICE_H