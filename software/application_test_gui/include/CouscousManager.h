#ifndef COUSCOUS_MANAGER_H
#define COUSCOUS_MANAGER_H

#include "Posi.h"
#include "WebServer.h"
#include <thread>

class CouscousManager {
public:
  CouscousManager();
  void start();

private:
  std::shared_ptr<Posi> posi_;
  std::shared_ptr<WebServer> web_server_;
  std::thread web_server_thread_;

  /**
   * @brief This method is called when posi updates its position and dispatch
   * the information to the web_server
   *
   * @param pos_x_m
   * @param pos_y_m
   * @param orientation_rad
   */
  void onPosiPositionUpdate(double pos_x_m, double pos_y_m,
                            double orientation_rad);

  /**
   * @brief Is called when the front calls to reset the absolute position
   *
   * @param pos_x_m
   * @param pos_y_m
   * @param orientation_rad
   */
  void onClientRequestSetPosition(double pos_x_m, double pos_y_m,
                                  double orientation_rad);
};

#endif // COUSCOUS_MANAGER_H