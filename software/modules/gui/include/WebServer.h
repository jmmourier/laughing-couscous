#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "WebPositionService.h"
#include "grpcpp/server.h"

class WebServer {
public:
  explicit WebServer(std::function<void(double pos_x_m, double pos_y_m,
                                        double orientation_rad)>
                         on_set_position_callback);

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

  void updatePosition(double pos_x_m, double pos_y_m, double orientation_rad);

private:
  std::shared_ptr<grpc::Server> server_;
  WebPositionService web_position_service_;
};

#endif // WEB_SERVER_H