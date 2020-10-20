#ifndef COUSCOUS_NAVI_H
#define COUSCOUS_NAVI_H

#include "NaviUtils.h"
#include "NaviStateMachine.h"
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


    int setTargetPosition(const double &target_pos_x, const double &target_pos_y, const double &target_orientation);
    int setTargetAngle(const double &target_orientation);
    int setCurrentPosition(const double &new_rob_pos_x, const double &new_rob_pos_y, const double &new_rob_orientation);
    int getPositionReached(void);
    int getActualState(void);
    void stateMachine(enumNaviStateMachine sm, pos_info robot_pos, pos_info target_pos);

private:

    pos_info target_position;
    pos_info actual_robot_position;

    //double alignToTarget(const double &robot_pos_x, const double &robot_pos_y, const double &robot_orientation, const double &target_pos_x, const double &target_pos_y);
    //void goToTarget(const double &pos_x, const double &pos_y);
    // float v_x_mps=0.f;
    // float v_y_mps=0.f;
    // float omega_radps=0.f;

    rotdir rotation_direction;
    enumNaviStateMachine actual_navi_state = enumNaviStateMachine::ST0_IDLE;
};


#endif //COUSCOUS_NAVI_H
