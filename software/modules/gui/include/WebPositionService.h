#ifndef WEB_POSITION_SERVICE_H
#define WEB_POSITION_SERVICE_H

#include "IWebServerRequestListener.h"
#include "robot.grpc.pb.h"

class WebPositionService final : public web_service::Position::Service {
   public:
    WebPositionService();

    void registerWebServerRequestListener(
        const std::weak_ptr<IWebServerRequestListener> &webserver_listener);

    void publishToWebServerPositionRequestListeners(
        const PositionOrientation &position_orientation) const;

    void publishToWebServerSpeedRequestListeners(const int &motor1, const int &motor2) const;

    void publishToWebServerTargetPositionListeners(const double &pos_x, const double &pos_y);
    void publishToWebServerTargetOrientationListeners(const float &orientation_rad);

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

    ::grpc::Status setTargetOrientationRequest(
        ::grpc::ServerContext *context,
        const ::web_service::OrientationRequest *request,
        ::web_service::Empty *response) override;

    void setPosition(const PositionOrientation &position_orientation);
    void setSpeed(const int &motor1, const int &motor2) const;

   private:
    PositionOrientation position_orientation_;
    std::vector<std::weak_ptr<IWebServerRequestListener>> webserver_listeners_;
};

#endif  // WEB_POSITION_SERVICE_H