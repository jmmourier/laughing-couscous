#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "IWebServerRequestListener.h"
#include "PositionOrientation.h"
#include "WebPositionService.h"
#include "grpcpp/server.h"

class WebServer {
   public:
    void registerWebServerRequestListener(
        const std::weak_ptr<IWebServerRequestListener> &webserver_listener);
    /**
     * @brief Create and launch web server and it's services
     *
     */
    void start();

    /**
     * @brief Shutsdown web server
     *
     */
    void stop();

    void setPosition(const PositionOrientation &position_orientation);
    void setBattery(const float &battery_v);
    void setGrabberState(const bool &is_grabber_open);
    void setMissionStartedAt(const long &mission_started_at);
    void setMissionEndedAt(const long &mission_ended_at);

    // void setSpeed(const int &motor1, const int &motor2);

   private:
    std::shared_ptr<grpc::Server> server_;
    WebPositionService web_position_service_;
};

#endif  // WEB_SERVER_H