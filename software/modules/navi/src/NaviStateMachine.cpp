#include "NaviStateMachine.h"
#include <iostream>


void naviStateMachineExec(const enumNaviStateMachine execState, enumNaviStateMachine next_state,  pos_info robot_pos, pos_info target_pos){

}

enumNaviStateMachine state1_start_align_to_target(pos_info robot_pos, pos_info target_pos){
    //std::cout << ">>>2)Send rotation command to hali. Rotate->:" << get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos));
    if (get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos)) == rotdir::Clockwise) {
        //rotate clockwise
    } else {
        //rotate anti-clockwise
    }
    return enumNaviStateMachine::ST2_ALIGN_TO_TARGET;
}

enumNaviStateMachine state2_align_to_target(pos_info robot_pos, pos_info target_pos){
    float delta_angle = get_angle_to_target(robot_pos, target_pos);
    if (get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos)) == rotdir::Clockwise) {
        if (std::abs(delta_angle) < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            return enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT;
        }
    } else {
        if (std::abs(delta_angle) < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            return enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT;
        }
    }
    return enumNaviStateMachine::ST2_ALIGN_TO_TARGET;
}

enumNaviStateMachine state3_wait_for_movement(){
    return enumNaviStateMachine::ST4_START_FW_MOVEMENT;
}

enumNaviStateMachine state4_start_fw() {
    return enumNaviStateMachine::ST5_DRIVING_TO_TARGET;
}

enumNaviStateMachine state5_driving_to_target(pos_info robot_pos, pos_info target_pos){
    if(get_distance_to_target(robot_pos, target_pos) < DELTA_DIST_TO_STOP_FW_MOVEMENT){
        return enumNaviStateMachine::ST7_START_ROTATION_TO_TARGET_ORIENTATION;
    }
    return enumNaviStateMachine::ST5_DRIVING_TO_TARGET;
}

enumNaviStateMachine state6_wait_for_rotation(){
    exit(0);
}
enumNaviStateMachine state7_start_rotation_to_target_orientation(pos_info robot_pos, pos_info target_pos){
    if (get_rotation_direction(robot_pos.orientation,target_pos.orientation) == rotdir::Clockwise) {
    } else {
    }
    return enumNaviStateMachine::ST8_ROTATION_TO_TARGET_ORIENTATION;
}

enumNaviStateMachine state8_rotation_to_target_orientation(pos_info robot_pos, pos_info target_pos){
    float delta_angle = get_angle_difference(robot_pos.orientation, target_pos.orientation);
    if (get_rotation_direction(robot_pos.orientation,target_pos.orientation) == rotdir::Clockwise) {
        if (std::abs(delta_angle) < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            return enumNaviStateMachine::ST9_DONE;
        }
    } else {
        if (std::abs(delta_angle) < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            return enumNaviStateMachine::ST9_DONE;
        }
    }
    return enumNaviStateMachine::ST8_ROTATION_TO_TARGET_ORIENTATION;
}

enumNaviStateMachine state9_done(){
    return enumNaviStateMachine::ST0_IDLE;
}