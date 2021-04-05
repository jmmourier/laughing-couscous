#include <gtest/gtest.h>

#include <cmath>

#include "Navi.h"
#include "NaviStateMachine.h"
#include "NaviUtils.h"

void dummy_init(float vx, float vy, float omega_rdps) {}

/*
TEST(NaviTest, standard_path) {
    pos_info target_position, rob_start_position, rob_point_aligned_to_target, rob_point2,
        rob_end_position;
    rob_start_position.pos_x = 0.0;
    rob_start_position.pos_y = 0.0;
    rob_start_position.orientation = 0.0;

    rob_point_aligned_to_target.pos_x = 0.1;
    rob_point_aligned_to_target.pos_y = 0.1;
    rob_point_aligned_to_target.orientation = M_PI / 4.0;

    rob_point2.pos_x = 0.2;
    rob_point2.pos_y = 0.2;
    rob_point2.orientation = 0.0;

    target_position.pos_x = 1.0;
    target_position.pos_y = 1.0;
    target_position.orientation = 0.0;


    Navi nav;

    // state0: idle
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST0_IDLE, nav.getActualState());
    nav.setCurrentPosition(
        rob_start_position.pos_x,
        rob_start_position.pos_y,
        rob_start_position.orientation);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST0_IDLE, nav.getActualState());
    // set target
    nav.setTargetPosition(
        target_position.pos_x,
        target_position.pos_y,
        target_position.orientation);
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST1_START_ALIGN_TO_TARGET,
        nav.getActualState());

    // state1: start rotation
    nav.setCurrentPosition(
        rob_start_position.pos_x,
        rob_start_position.pos_y,
        rob_start_position.orientation);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST2_ALIGN_TO_TARGET, nav.getActualState());

    // state2: rotation to target
    nav.setCurrentPosition(
        rob_start_position.pos_x,
        rob_start_position.pos_y,
        rob_start_position.orientation);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST2_ALIGN_TO_TARGET, nav.getActualState());
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, M_PI / 4);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST3_WAIT_FOR_MOVMENT, nav.getActualState());

    // state3: wait for movement
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, M_PI / 4);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST4_START_FW_MOVEMENT, nav.getActualState());

    // state4: start fw movement
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, M_PI / 4);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST5_DRIVING_TO_TARGET, nav.getActualState());

    // state5: driving to target
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, M_PI / 4);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST5_DRIVING_TO_TARGET, nav.getActualState());
    nav.setCurrentPosition(
        target_position.pos_x,
        target_position.pos_y - (DELTA_DIST_TO_STOP_FW_MOVEMENT * 2),
        M_PI / 4);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST5_DRIVING_TO_TARGET, nav.getActualState());
    nav.setCurrentPosition(
        target_position.pos_x,
        target_position.pos_y - DELTA_DIST_TO_STOP_FW_MOVEMENT,
        M_PI / 4);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST6_WAIT_FOR_ROTATION, nav.getActualState());

    // state6:wait for rotation
    nav.setCurrentPosition(target_position.pos_x, target_position.pos_y, M_PI / 4);
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST7_START_ROTATION_TO_TARGET_ORIENTATION,
        nav.getActualState());

    // state7: start rotation to target orientation
    nav.setCurrentPosition(target_position.pos_x, target_position.pos_y, M_PI / 4);
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST8_ROTATION_TO_TARGET_ORIENTATION,
        nav.getActualState());

    // state8: rotation in progress
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, M_PI / 4);
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST8_ROTATION_TO_TARGET_ORIENTATION,
        nav.getActualState());
    nav.setCurrentPosition(
        rob_start_position.pos_x,
        rob_start_position.pos_y,
        target_position.orientation);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST9_DONE, nav.getActualState());

    // state9: done
    nav.setCurrentPosition(
        rob_start_position.pos_x,
        rob_start_position.pos_y,
        target_position.orientation);
    EXPECT_EQ(NaviStateMachine::NaviStateMachineEnum::ST0_IDLE, nav.getActualState());
}
*/