#ifndef COUSCOUS_ROBOTCONTROLLER_H
#define COUSCOUS_ROBOTCONTROLLER_H

#include <memory>
#include <thread>
#include "Hali.h"
#include "Posi.h"
#include <Navi.h>
#include <Moti.h>

class RobotController {
   public:
    explicit RobotController(std::shared_ptr<Hali> hali);
    void start();
    /**
       * @brief Is called when the front calls to reset the absolute position
       *
       * @param pos_x_m
       * @param pos_y_m
       * @param orientation_rad
       */
    void onClientRequestSetPosition(double pos_x_m, double pos_y_m, double orientation_rad);
   private:
    std::shared_ptr<Posi> posi_;
    std::shared_ptr<Hali> hali_;
    std::shared_ptr<Navi> nav_;
    //std::shared_ptr<Moti> moti_;
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
     * @brief Is called when the front calls to set robot's speed
     *
     * @param motor1
     * @param motor2
     */
    //void onClientRequestSetSpeed(int motor1, int motor2);
    void onClientRequestSetSpeed(float vx, float vy, float omega);

};

#endif  // COUSCOUS_ROBOTCONTROLLER_H
