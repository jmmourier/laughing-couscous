#ifndef WEB_POSITION_SERVICE_H
#define WEB_POSITION_SERVICE_H

#include "IWebServerListener.h"
#include "robot.grpc.pb.h"

class WebPositionService final : public web_service::Position::Service {
   public:
    void registerWebServerListener(const std::weak_ptr<IWebServerListener> &webserver_listener);

    void publishToPositionRequestListeners(
        const double &pos_x,
        const double &pos_y,
        const double &orientation) const;

    void publishToSpeedRequestListeners(const int &motor1, const int &motor2) const;

    void publishToTargetPositionListeners(const double &pos_x, const double &pos_y);

    ::grpc::Status setSpeedRequest(
        ::grpc::ServerContext *context,
        const ::web_service::SpeedRequest *request,
        ::web_service::Empty *response) override;

    ::grpc::Status registerPositionObserver(
        ::grpc::ServerContext *context,
        const ::web_service::Empty *request,
        ::grpc::ServerWriter<::web_service::PositionOrientationRequest> *writer) override;

    ::grpc::Status setAbsolutePositionRequest(
        ::grpc::ServerContext *context,
        const ::web_service::PositionOrientationRequest *request,
        ::web_service::Empty *response) override;

    ::grpc::Status setTargetPositionRequest(
        ::grpc::ServerContext *context,
        const ::web_service::PositionRequest *request,
        ::web_service::Empty *response) override;

    void setPosition(const double &pos_x_m, const double &pos_y_m, const double &orientation_rad);
    void setSpeed(const int &motor1, const int &motor2) const;

   private:
    double pos_x_m_;
    double pos_y_m_;
    double orientation_rad_;
    std::vector<std::weak_ptr<IWebServerListener>> webserver_listeners_;
};

#endif  // WEB_POSITION_SERVICE_H