#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "IWebServerListener.h"
#include "WebPositionService.h"
#include "grpcpp/server.h"

class WebServer {
   public:
    void registerWebServerListener(const std::weak_ptr<IWebServerListener> &webserver_listener);
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

    void setPosition(const double &pos_x_m, const double &pos_y_m, const double &orientation_rad);

    // void setSpeed(const int &motor1, const int &motor2);

   private:
    std::shared_ptr<grpc::Server> server_;
    WebPositionService web_position_service_;
};

#endif  // WEB_SERVER_H