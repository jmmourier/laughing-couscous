#ifndef COUSCOUS_NAVI_H
#define COUSCOUS_NAVI_H

#include <spdlog/logger.h>

#include <functional>
#include <memory>

#include "INaviRequestListener.h"
#include "NaviStateMachine.h"
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

    //  Navi(std::function<void(float vx, float vy, float omega_rdps)> on_set_speed_callback);
    int setTargetPosition(
        const double &target_pos_x,
        const double &target_pos_y,
        const double &target_orientation);
    int setCurrentPosition(
        const double &new_rob_pos_x,
        const double &new_rob_pos_y,
        const double &new_rob_orientation);
    int getPositionReached();
    int getActualState();
    void stateMachine(
        NaviStateMachine::NaviStateMachineEnum sm,
        pos_info robot_pos,
        pos_info target_pos);

   private:
    bool target_reached = false;
    pos_info target_position_;
    pos_info actual_robot_position_;
    rotdir rotation_direction_;
    NaviStateMachine::NaviStateMachineEnum current_navi_state_ =
        NaviStateMachine::NaviStateMachineEnum::ST0_IDLE;
    // std::function<void(float vx, float vy, float omega_rdps)> on_set_speed_callback_;
    NaviStateMachine navi_state_machine_;
    std::shared_ptr<spdlog::logger> logger_;
};

#endif  // COUSCOUS_NAVI_H
