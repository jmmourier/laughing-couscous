#include "Navi.h"

#include <iostream>

#include "NaviUtils.h"

void Navi::registerNaviRequestListener(const std::weak_ptr<INaviRequestListener> &navi_listener) {
    navi_state_machine_.registerNaviSMRequestListener(navi_listener);
}

/**
 *
 * @param target_pos_x
 * @param target_pos_y
 * @param target_orientation
 * @returnf
 */
int Navi::setTargetPosition(
    const double &target_pos_x,
    const double &target_pos_y,
    const double &target_orientation) {
    std::cout << "[Nav] set target position" << target_pos_x << " " << target_pos_y << std::endl;
    target_position_.pos_x = target_pos_x;
    target_position_.pos_y = target_pos_y;
    target_position_.orientation = target_orientation;
    current_navi_state_ = NaviStateMachine::NaviStateMachineEnum::ST1_START_ALIGN_TO_TARGET;
    target_reached = false;
    return 0;
}

void Navi::stateMachine(
    NaviStateMachine::NaviStateMachineEnum sm,
    pos_info robot_pos,
    pos_info target_pos) {
    switch (sm) {
        case NaviStateMachine::NaviStateMachineEnum::ST0_IDLE:
            // state changed by setTargetPosition()
            break;
        case NaviStateMachine::NaviStateMachineEnum::ST1_START_ALIGN_TO_TARGET:
            current_navi_state_ = navi_state_machine_.startAlignToTarget(robot_pos, target_pos);
            break;
        case NaviStateMachine::NaviStateMachineEnum::ST2_ALIGN_TO_TARGET:
            current_navi_state_ = navi_state_machine_.alignToTarget(robot_pos, target_pos);
            break;
        case NaviStateMachine::NaviStateMachineEnum::ST3_WAIT_FOR_MOVMENT:
            current_navi_state_ = navi_state_machine_.waitForMovement();
            break;
        case NaviStateMachine::NaviStateMachineEnum::ST4_START_FW_MOVEMENT:
            current_navi_state_ = navi_state_machine_.startFw();
            break;
        case NaviStateMachine::NaviStateMachineEnum::ST5_DRIVING_TO_TARGET:
            current_navi_state_ = navi_state_machine_.drivingToTarget(robot_pos, target_pos);
            break;
        case NaviStateMachine::NaviStateMachineEnum::ST9_DONE:
            current_navi_state_ = navi_state_machine_.done();
            target_reached = true;
            break;
        default:
            break;
    }
}

int Navi::setCurrentPosition(
    const double &new_rob_pos_x,
    const double &new_rob_pos_y,
    const double &new_rob_orientation) {
    actual_robot_position_.pos_x = new_rob_pos_x;
    actual_robot_position_.pos_y = new_rob_pos_y;
    actual_robot_position_.orientation = new_rob_orientation;
    stateMachine(current_navi_state_, actual_robot_position_, target_position_);
    // std::cout << "update position" << std::endl;
    return 0;
}

int Navi::getPositionReached() {
    return target_reached;
}

int Navi::getActualState() {
    // return current_navi_state_;
    return 0;
}