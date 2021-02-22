
#ifndef COUSCOUS_NAVISTATEMACHINE_H
#define COUSCOUS_NAVISTATEMACHINE_H

#include <functional>

#include "NaviUtils.h"

#define DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT 0.05
#define DELTA_DIST_TO_STOP_FW_MOVEMENT 0.1

enum enumNaviStateMachine {
    ST0_IDLE,
    ST1_START_ALIGN_TO_TARGET,
    ST2_ALIGN_TO_TARGET,
    ST3_WAIT_FOR_MOVMENT,
    ST4_START_FW_MOVEMENT,
    ST5_DRIVING_TO_TARGET,
    ST6_WAIT_FOR_ROTATION,
    ST7_START_ROTATION_TO_TARGET_ORIENTATION,
    ST8_ROTATION_TO_TARGET_ORIENTATION,
    ST9_DONE
};
void naviStateMachineExec(
    const enumNaviStateMachine execState,
    enumNaviStateMachine next_state,
    pos_info robot_pos,
    pos_info target_pos);
// void state_idle();
enumNaviStateMachine state1_start_align_to_target(
    pos_info robot_pos,
    pos_info target_pos,
    std::function<void(float vx, float vy, float omega_rdps)> on_set_speed_callbac);
enumNaviStateMachine state2_align_to_target(
    pos_info robot_pos,
    pos_info target_pos,
    std::function<void(float vx, float vy, float omega_rdps)> on_set_speed_callback);
enumNaviStateMachine state3_wait_for_movement();
enumNaviStateMachine state4_start_fw(
    std::function<void(float vx, float vy, float omega)> on_set_speed_callback);
enumNaviStateMachine state5_driving_to_target(
    pos_info robot_pos,
    pos_info target_pos,
    std::function<void(float vx, float vy, float omega_rdps)> on_set_speed_callback);
enumNaviStateMachine state6_wait_for_rotation();
enumNaviStateMachine state7_start_rotation_to_target_orientation(
    pos_info robot_pos,
    pos_info target_pos,
    std::function<void(float vx, float vy, float omega_rdps)> on_set_speed_callback);
enumNaviStateMachine state8_rotation_to_target_orientation(pos_info robot_pos, pos_info target_pos);
enumNaviStateMachine state9_done(
    std::function<void(float vx, float vy, float omega_rdps)> on_set_speed_callback);

#endif  // COUSCOUS_NAVISTATEMACHINE_H
