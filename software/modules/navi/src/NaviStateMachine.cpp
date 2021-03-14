#include "NaviStateMachine.h"

#include <iostream>

//#define WHEEL_SPEED 1.0
//#define ROTATION_SPEED 10.0

#define WHEEL_SPEED_BASE 300  // 127
#define WHEEL_SPEED_STOP 127  // 127
#define WHEEL_SPEED_FW WHEEL_SPEED_STOP + WHEEL_SPEED_BASE
#define WHEEL_SPEED_BW WHEEL_SPEED_STOP - WHEEL_SPEED_BASE

void NaviStateMachine::registerNaviSMRequestListener(
    const std::weak_ptr<INaviRequestListener> &navi_listener) {
    navi_listeners_.push_back(navi_listener);
}

void NaviStateMachine::publishToNaviSpeedRequestListeners(const int &motor1, const int &motor2)
    const {
    for (auto const &navi_listener_ptr : navi_listeners_) {
        if (auto navi_listener = navi_listener_ptr.lock()) {
            navi_listener->onNaviSpeedRequest(motor1, motor2);
        }
    }
}

void NaviStateMachine::publishToNaviTargetReachedListeners(void) const {
    for (auto const &navi_listener_ptr : navi_listeners_) {
        if (auto navi_listener = navi_listener_ptr.lock()) {
            navi_listener->onNaviTargetReachedRequest();
        }
    }
}

/**
 * Start rotation to be aligned to the target
 * @param robot_pos
 * @param target_pos
 * @param on_set_speed_callback
 * @return
 */
NaviStateMachine::NaviStateMachineEnum NaviStateMachine::startAlignToTarget(
    pos_info robot_pos,
    pos_info target_pos) {
    std::cout << "navi_state_machine -1-: start rotation"
              << getReferenceAngleToTarget(robot_pos, target_pos) << std::endl;

    if (getReferenceAngleToTarget(robot_pos, target_pos) == 0) {
        return NaviStateMachineEnum::ST4_START_FW_MOVEMENT;
    }
    if (getRotationDirection(
            robot_pos.orientation,
            getReferenceAngleToTarget(robot_pos, target_pos)) == rotdir::Clockwise) {
        // rotate clockwise
        std::cout << "rotate clockwise" << std::endl;
        publishToNaviSpeedRequestListeners(WHEEL_SPEED_BW, WHEEL_SPEED_FW);
        //  on_set_speed_callback(0, 0, ROTATION_SPEED);
    } else {
        // rotate anti-clockwise
        std::cout << "rotate anti-clockwise" << std::endl;
        publishToNaviSpeedRequestListeners(WHEEL_SPEED_FW, WHEEL_SPEED_BW);
        // on_set_speed_callback(0, 0, -ROTATION_SPEED);
    }
    return NaviStateMachineEnum::ST2_ALIGN_TO_TARGET;
}

/**
 * Rotate until robot orientation is aligned to the target
 * @param robot_pos
 * @param target_pos
 * @param on_set_speed_callback
 * @return
 */
NaviStateMachine::NaviStateMachineEnum NaviStateMachine::alignToTarget(
    pos_info robot_pos,
    pos_info target_pos) {
    float delta_angle = getAngleToTargetFrom(robot_pos, target_pos);
    std::cout << "navi_state_machine -2-: align to target" << std::endl;
    std::cout << "robot angle:" << robot_pos.orientation << " delta angle:"
              << delta_angle
              //  << " target angle : " << get_reference_angle_to_target(robot_pos, target_pos)
              << std::endl;
    if (getRotationDirection(
            robot_pos.orientation,
            getReferenceAngleToTarget(robot_pos, target_pos)) == rotdir::Clockwise) {
        if (std::abs(delta_angle) < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            publishToNaviSpeedRequestListeners(WHEEL_SPEED_STOP, WHEEL_SPEED_STOP);
            // on_set_speed_callback(0, 0, 0);
            return NaviStateMachineEnum::ST3_WAIT_FOR_MOVMENT;
        }
    } else {
        if (std::abs(delta_angle) < DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT) {
            publishToNaviSpeedRequestListeners(WHEEL_SPEED_STOP, WHEEL_SPEED_STOP);
            // on_set_speed_callback(0, 0, 0);
            return NaviStateMachineEnum::ST3_WAIT_FOR_MOVMENT;
        }
    }
    return NaviStateMachineEnum::ST2_ALIGN_TO_TARGET;
}

/**
 *
 * @return
 */
NaviStateMachine::NaviStateMachine::NaviStateMachineEnum NaviStateMachine::waitForMovement() {
    return NaviStateMachineEnum::ST4_START_FW_MOVEMENT;
}

NaviStateMachine::NaviStateMachineEnum NaviStateMachine::startFw() {
    std::cout << "navi_state_machine -4-: FW" << std::endl;
    publishToNaviSpeedRequestListeners(WHEEL_SPEED_FW, WHEEL_SPEED_FW);
    // on_set_speed_callback(WHEEL_SPEED, 0, 0);
    return NaviStateMachineEnum::ST5_DRIVING_TO_TARGET;
}

NaviStateMachine::NaviStateMachineEnum NaviStateMachine::drivingToTarget(
    pos_info robot_pos,
    pos_info target_pos) {
    std::cout << "navi_state_machine -5-: driving" << std::endl;
    if (getDistanceToTarget(robot_pos, target_pos) < DELTA_DIST_TO_STOP_FW_MOVEMENT) {
        publishToNaviSpeedRequestListeners(WHEEL_SPEED_STOP, WHEEL_SPEED_STOP);
        // on_set_speed_callback(0, 0, 0);
        return NaviStateMachineEnum::ST9_DONE;
    }
    return NaviStateMachineEnum::ST5_DRIVING_TO_TARGET;
}

NaviStateMachine::NaviStateMachineEnum NaviStateMachine::done() {
    publishToNaviSpeedRequestListeners(WHEEL_SPEED_STOP, WHEEL_SPEED_STOP);
    publishToNaviTargetReachedListeners();
    // on_set_speed_callback(0, 0, 0);
    // exit(0);
    return NaviStateMachineEnum::ST0_IDLE;
}