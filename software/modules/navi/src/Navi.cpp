
#include "Navi.h"
#include "NaviUtils.h"
#include <iostream>


/**
*
* @param target_pos_x
* @param target_pos_y
* @param target_orientation
* @returnf
*/
int Navi::setTargetPosition(const double &target_pos_x, const double &target_pos_y, const double &target_orientation){
    target_position.pos_x = target_pos_x;
    target_position.pos_y = target_pos_y;
    target_position.orientation = target_orientation;
    actual_navi_state = enumNaviStateMachine::ST1_START_ALIGN_TO_TARGET;
    target_reached = false;
    return 0;
}

void Navi::stateMachine(enumNaviStateMachine sm , pos_info robot_pos, pos_info target_pos){
    switch(sm) {
        case enumNaviStateMachine::ST0_IDLE:
            //state changed by setTargetPosition()
            break;
        case enumNaviStateMachine::ST1_START_ALIGN_TO_TARGET:
            actual_navi_state = state1_start_align_to_target(robot_pos, target_pos);
            break;
        case enumNaviStateMachine::ST2_ALIGN_TO_TARGET:
            actual_navi_state = state2_align_to_target(robot_pos, target_pos);
            break;
        case enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT:
            actual_navi_state = state3_wait_for_movement();
            break;
        case enumNaviStateMachine::ST4_START_FW_MOVEMENT:
            actual_navi_state = state4_start_fw();
            break;
        case enumNaviStateMachine::ST5_DRIVING_TO_TARGET:
            actual_navi_state = state5_driving_to_target(robot_pos, target_pos);
            break;
        case enumNaviStateMachine::ST6_WAIT_FOR_ROTATION:
            actual_navi_state = state6_wait_for_rotation();
            break;
        case enumNaviStateMachine::ST7_START_ROTATION_TO_TARGET_ORIENTATION:
            actual_navi_state = state7_start_rotation_to_target_orientation(robot_pos, target_pos);
            break;
        case enumNaviStateMachine::ST8_ROTATION_TO_TARGET_ORIENTATION:
            actual_navi_state = state8_rotation_to_target_orientation(robot_pos, target_pos);
            break;
        case enumNaviStateMachine::ST9_DONE:
            target_reached = true;
            break;
        default:
            break;
    }

}

int Navi::setCurrentPosition(const double &new_rob_pos_x, const double &new_rob_pos_y, const double &new_rob_orientation){
    actual_robot_position.pos_x = new_rob_pos_x;
    actual_robot_position.pos_y = new_rob_pos_y;
    actual_robot_position.orientation = new_rob_orientation;
    stateMachine(actual_navi_state, actual_robot_position, target_position);
    return 0;
}


int Navi::getPositionReached(void){
    return target_reached;
}

int Navi::getActualState(void){
    return actual_navi_state;
}



/*
double Navi::alignToTarget(const double &robot_pos_x, const double &robot_pos_y, const double &robot_orientation, const double &target_pos_x, const double &target_pos_y){
    return 0.0;
}
void Navi::goToTarget(const double &pos_x, const double &pos_y){
}
*/
/*
RobotBaseSpeed Navi::getBaseSpeed() {
    RobotBaseSpeed baseSpeed(v_x_mps, v_y_mps, omega_radps);
    return baseSpeed;
}*/
