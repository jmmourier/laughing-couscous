#ifndef COUSCOUS_MANAGER_GUI_H
#define COUSCOUS_MANAGER_GUI_H

#include <thread>

#include "Hali.h"
#include "Posi.h"
#include "WebServer.h"

class CouscousManagerGui {
   public:
    explicit CouscousManagerGui(std::shared_ptr<Hali> hali);
    void start();

   private:
    std::shared_ptr<Posi> posi_;
    std::shared_ptr<Hali> hali_;
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
    void onPosiPositionUpdate(double pos_x_m, double pos_y_m, double orientation_rad);

    /**
     * @brief Is called when the front calls to reset the absolute position
     *
     * @param pos_x_m
     * @param pos_y_m
     * @param orientation_rad
     */
    void onClientRequestSetPosition(double pos_x_m, double pos_y_m, double orientation_rad);

    /**
     * @brief Is called when the front calls to set robot's speed
     *
     * @param motor1
     * @param motor2
     */
    void onClientRequestSetSpeed(int motor1, int motor2);
};

#endif  // COUSCOUS_MANAGER_GUI_H