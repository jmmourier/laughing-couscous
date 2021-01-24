#include "NaviStateMachine.h"
#include <iostream>

#define WHEEL_ROTATION_SPEED 1
#define WHEEL_FW_SPEED 1
void naviStateMachineExec(const enumNaviStateMachine execState, enumNaviStateMachine next_state,  pos_info robot_pos, pos_info target_pos){

}

/**
 * Start rotation to be aligned to the target
 * @param robot_pos
 * @param target_pos
 * @param on_set_speed_callback
 * @return
 */
enumNaviStateMachine state1_start_align_to_target(pos_info robot_pos, pos_info target_pos, std::function<void(int motor1, int motor2)> on_set_speed_callback){
    //std::cout << ">>>2)Send rotation command to hali. Rotate->:" << get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos));
    if (get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos)) == rotdir::Clockwise) {
        //rotate clockwise
        on_set_speed_callback(WHEEL_ROTATION_SPEED,-WHEEL_ROTATION_SPEED);
    } else {
        //rotate anti-clockwise
        on_set_speed_callback(-WHEEL_ROTATION_SPEED,WHEEL_ROTATION_SPEED);
    }
    return enumNaviStateMachine::ST2_ALIGN_TO_TARGET;
}

/**
 * Rotate until robot orientation is aligned to the target
 * @param robot_pos
 * @param target_pos
 * @param on_set_speed_callback
 * @return
 */
enumNaviStateMachine state2_align_to_target(pos_info robot_pos, pos_info target_pos, std::function<void(int motor1, int motor2)> on_set_speed_callback){
    float delta_angle = get_angle_to_target(robot_pos, target_pos);
    if (get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos)) == rotdir::Clockwise) {
        if (std::abs(delta_angle) < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            on_set_speed_callback(0,0);
            return enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT;
        }
    } else {
        if (std::abs(delta_angle) < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            on_set_speed_callback(0,0);
            return enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT;
        }
    }
    return enumNaviStateMachine::ST2_ALIGN_TO_TARGET;
}

/**
 *
 * @return
 */
enumNaviStateMachine state3_wait_for_movement(){
    return enumNaviStateMachine::ST4_START_FW_MOVEMENT;
}

enumNaviStateMachine state4_start_fw(std::function<void(int motor1, int motor2)> on_set_speed_callback) {
    on_set_speed_callback(WHEEL_FW_SPEED,WHEEL_FW_SPEED);
    return enumNaviStateMachine::ST5_DRIVING_TO_TARGET;
}

enumNaviStateMachine state5_driving_to_target(pos_info robot_pos, pos_info target_pos, std::function<void(int motor1, int motor2)> on_set_speed_callback){
    if(get_distance_to_target(robot_pos, target_pos) < DELTA_DIST_TO_STOP_FW_MOVEMENT){
        on_set_speed_callback(0,0);
        return enumNaviStateMachine::ST6_WAIT_FOR_ROTATION;
    }
    return enumNaviStateMachine::ST5_DRIVING_TO_TARGET;
}

enumNaviStateMachine state6_wait_for_rotation(){
    return enumNaviStateMachine::ST7_START_ROTATION_TO_TARGET_ORIENTATION;
}
enumNaviStateMachine state7_start_rotation_to_target_orientation(pos_info robot_pos, pos_info target_pos, std::function<void(int motor1, int motor2)> on_set_speed_callback){
    if (get_rotation_direction(robot_pos.orientation,target_pos.orientation) == rotdir::Clockwise) {
        //turn robot clockwise
        on_set_speed_callback(WHEEL_ROTATION_SPEED,-WHEEL_ROTATION_SPEED);
    } else {
        on_set_speed_callback(-WHEEL_ROTATION_SPEED,WHEEL_ROTATION_SPEED);
        //turn robot anti-clockwise
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

enumNaviStateMachine state9_done(std::function<void(int motor1, int motor2)> on_set_speed_callback){
    on_set_speed_callback(0,0);
    return enumNaviStateMachine::ST0_IDLE;
}