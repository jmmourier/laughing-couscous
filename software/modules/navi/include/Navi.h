#ifndef COUSCOUS_NAVI_H
#define COUSCOUS_NAVI_H

#include "NaviUtils.h"
#include "NaviStateMachine.h"
#include <functional>
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
    Navi(std::function<void(int motor1, int motor2)> on_set_speed_callback);
    int setTargetPosition(const double &target_pos_x, const double &target_pos_y, const double &target_orientation);
    int setCurrentPosition(const double &new_rob_pos_x, const double &new_rob_pos_y, const double &new_rob_orientation);
    int getPositionReached(void);
    int getActualState(void);
    void stateMachine(enumNaviStateMachine sm, pos_info robot_pos, pos_info target_pos);

private:
    bool target_reached = false;
    pos_info target_position;
    pos_info actual_robot_position;
    rotdir rotation_direction;
    enumNaviStateMachine actual_navi_state = enumNaviStateMachine::ST0_IDLE;
    std::function<void(int motor1, int motor2)> on_set_speed_callback_;
};


#endif //COUSCOUS_NAVI_H
