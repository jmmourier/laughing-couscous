#include "NaviStateMachine.h"
#include <iostream>


void naviStateMachineExec(const enumNaviStateMachine execState, enumNaviStateMachine next_state,  pos_info robot_pos, pos_info target_pos){

}

enumNaviStateMachine state1_start_align_to_target(pos_info robot_pos, pos_info target_pos){
    //std::cout << ">>>2)Send rotation command to hali. Rotate->:" << get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos));
    if (get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos)) == rotdir::Clockwise) {
        //std::cout<<" clockwise"<<std::endl;
    } else {
        //std::cout<<" anticlockwise"<<std::endl;
    }
    return enumNaviStateMachine::ST2_ALIGN_TO_TARGET;
}

enumNaviStateMachine state2_align_to_target(pos_info robot_pos, pos_info target_pos){
    float delta_angle = std::abs(robot_pos.orientation - get_reference_angle_to_target(robot_pos, target_pos));
    if (get_rotation_direction(robot_pos.orientation,get_reference_angle_to_target(robot_pos, target_pos)) == rotdir::Clockwise) {
        if (delta_angle < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {  //! bug if angle near 0 and near 2pi
            //std::cout << ">>>3)clockwise turn done" << std::endl;
            return enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT;
        }
    } else {
        //std::cout<<" anticlockwise"<<std::endl;
        if (delta_angle < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {  //! bug if angle near 0 and near 2pi
            //std::cout << ">>>3)anticlockwise turn done" << std::endl;
            return enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT;
        }
    }
    return enumNaviStateMachine::ST2_ALIGN_TO_TARGET;
}

enumNaviStateMachine state3_wait_for_movement(){
    //std::cout << ">>>4)wait before movement" << std::endl;
    return enumNaviStateMachine::ST4_START_FW_MOVEMENT;
}

enumNaviStateMachine state4_start_fw() {
    //std::cout << ">>>5)start fw movement" << std::endl;
    return enumNaviStateMachine::ST5_DRIVING_TO_TARGET;
}

enumNaviStateMachine state5_driving_to_target(pos_info robot_pos, pos_info target_pos){
    //std::cout << ">>>6)driving to target, remaining dist:" << get_distance_to_target(robot_pos, target_pos) << std::endl;
    if(get_distance_to_target(robot_pos, target_pos) < DELTA_DIST_TO_STOP_FW_MOVEMENT){
        //std::cout<<">>>6')target reached "<<std::endl;
        //std::cout<<"stop motors"<<std::endl;
        return enumNaviStateMachine::ST7_START_ROTATION_TO_TARGET_ORIENTATION;
    }
    return enumNaviStateMachine::ST5_DRIVING_TO_TARGET;
}

enumNaviStateMachine state6_wait_for_rotation(){
    exit(0);
}
enumNaviStateMachine state7_start_rotation_to_target_orientation(pos_info robot_pos, pos_info target_pos){
    //std::cout << ">>>7)Send rotation command to hali. Rotate->:" <<  get_rotation_direction(robot_pos.orientation,target_pos.orientation);
    if (get_rotation_direction(robot_pos.orientation,target_pos.orientation) == rotdir::Clockwise) {
        //std::cout<<" clockwise"<<std::endl;
    } else {
        //std::cout<<" anticlockwise"<<std::endl;
    }
    return enumNaviStateMachine::ST8_ROTATION_TO_TARGET_ORIENTATION;
}

enumNaviStateMachine state8_rotation_to_target_orientation(pos_info robot_pos, pos_info target_pos){
    //float delta_angle = std::abs(robot_pos.orientation - target_pos.orientation);
    float delta_angle = get_angle_difference(robot_pos.orientation, target_pos.orientation);
    if (get_rotation_direction(robot_pos.orientation,target_pos.orientation) == rotdir::Clockwise) {
        //std::cout<<">>>8) turning"<<std::endl;
        if (delta_angle < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            //std::cout << ">>>)clockwise turn done" << std::endl;
            return enumNaviStateMachine::ST9_DONE;
        }
    } else {
        //std::cout<<" anticlockwise"<<std::endl;
        if (delta_angle < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            //std::cout << ">>>)anticlockwise turn done" << std::endl;
            return enumNaviStateMachine::ST9_DONE;
        }
    }
    return enumNaviStateMachine::ST8_ROTATION_TO_TARGET_ORIENTATION;
}

enumNaviStateMachine state9_done(){
    return enumNaviStateMachine::ST0_IDLE;
}