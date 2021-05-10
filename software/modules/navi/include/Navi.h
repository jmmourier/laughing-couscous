#ifndef COUSCOUS_NAVI_H
#define COUSCOUS_NAVI_H

#include <spdlog/logger.h>

#include <functional>
#include <memory>

#include "INaviRequestListener.h"
//#include "NaviRegulator.h"
//#include "NaviStateMachine.h"
#include "NaviUtils.h"
/*
struct RobotBaseSpeed
{
    RobotBaseSpeed(float v_x_mps,float v_y_mps,float omega_radps) :
            v_x_mps_(v_x_mps),
            v_y_mps_(v_y_mps),
            omega_radps_(omega_radps) {};
    float v_x_mps_, v_y_mps_, omega_radps_;
};*/

class Navi {
   public:
    explicit Navi();
    void registerNaviRequestListener(const std::weak_ptr<INaviRequestListener> &navi_listener);
    // void publishToNaviSpeedRequestListeners(const int &motor1, const int &motor2) const;
    void publishToNaviSpeedRequestListeners(
        const float &v_x_mps,
        const float &v_y_mps,
        const float &omega_radps) const;
    void publishToNaviTargetReachedListeners(void) const;

    int setTargetPosition(
        const double &target_pos_x,
        const double &target_pos_y,
        const double &target_orientation);
    int setTargetOrientation(const float &orientation_rad);
    int setCurrentPosition(
        const double &new_rob_pos_x,
        const double &new_rob_pos_y,
        const double &new_rob_orientation);

   private:
    void computeSpeed(const pos_info &robot_pos, const pos_info &target_pos);
    pos_info target_position_;
    pos_info actual_robot_position_;
    std::shared_ptr<spdlog::logger> logger_;
    std::vector<std::weak_ptr<INaviRequestListener>> navi_listeners_;
    bool is_idle_ = true;
};

#endif  // COUSCOUS_NAVI_H
