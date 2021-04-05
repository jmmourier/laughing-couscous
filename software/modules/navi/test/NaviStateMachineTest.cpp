#include <NaviStateMachine.h>
#include <gtest/gtest.h>

#include <cmath>
//void dummy_lambda(float vx, float vy, float omega_rdps) {}
NaviStateMachine navi_state_machine_;
/*
TEST(NaviStateMachineTest, start_align_to_target_1) {
    pos_info robot_pos, target_pos;
    robot_pos.pos_x = 0.0;
    robot_pos.pos_y = 0.0;
    robot_pos.orientation = 0.0;
    robot_pos.pos_x = 1.0;
    robot_pos.pos_y = 1.0;
    robot_pos.orientation = 1.0;
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST2_ALIGN_TO_TARGET,
        navi_state_machine_.startAlignToTarget(robot_pos, target_pos));
}

TEST(NaviStateMachineTest, align_to_target_2) {
    pos_info robot_pos, target_pos;
    // anticlockwise
    robot_pos.pos_x = 0.0;
    robot_pos.pos_y = 0.0;
    robot_pos.orientation = 0.0;
    target_pos.pos_x = 1.0;
    target_pos.pos_y = 1.0;
    target_pos.orientation = 1.0;
    // turning in progress
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST2_ALIGN_TO_TARGET,
        navi_state_machine_.alignToTarget(robot_pos, target_pos, dummy_lambda));
    // turning done
    robot_pos.orientation = M_PI / 4;
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST3_WAIT_FOR_MOVMENT,
        navi_state_machine_.alignToTarget(robot_pos, target_pos, dummy_lambda));

    // clockwise
    robot_pos.orientation = M_PI / 4 + 1;
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST2_ALIGN_TO_TARGET,
        navi_state_machine_.alignToTarget(robot_pos, target_pos, dummy_lambda));
    robot_pos.orientation = M_PI / 4;
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST3_WAIT_FOR_MOVMENT,
        navi_state_machine_.alignToTarget(robot_pos, target_pos, dummy_lambda));
}

TEST(NaviStateMachineTest, driving_to_target_5) {
    pos_info robot_pos, target_pos;
    robot_pos.pos_x = 0.0;
    robot_pos.pos_y = 0.0;
    robot_pos.orientation = 0.0;
    target_pos.pos_x = 1.0;
    target_pos.pos_y = 1.0;
    target_pos.orientation = 1.0;
    // target not reached
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST5_DRIVING_TO_TARGET,
        navi_state_machine_.drivingToTarget(robot_pos, target_pos, dummy_lambda));
    // target reached
    robot_pos.pos_x = target_pos.pos_x - (DELTA_DIST_TO_STOP_FW_MOVEMENT / 1.42);
    robot_pos.pos_y = target_pos.pos_y - (DELTA_DIST_TO_STOP_FW_MOVEMENT / 1.42);
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST6_WAIT_FOR_ROTATION,
        navi_state_machine_.drivingToTarget(robot_pos, target_pos, dummy_lambda));
}

TEST(NaviStateMachineTest, rotation_to_target_orientation_8) {
    pos_info robot_pos, target_pos;
    robot_pos.pos_x = 0.0;
    robot_pos.pos_y = 0.0;
    robot_pos.orientation = 0.0;
    target_pos.pos_x = 1.0;
    target_pos.pos_y = 1.0;
    target_pos.orientation = 1.0;
    // turning in progress
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST8_ROTATION_TO_TARGET_ORIENTATION,
        navi_state_machine_.rotationToTargetOrientation(robot_pos, target_pos));
    // turning done
    robot_pos.orientation = 1.0;
    EXPECT_EQ(
        NaviStateMachine::NaviStateMachineEnum::ST9_DONE,
        navi_state_machine_.rotationToTargetOrientation(robot_pos, target_pos));
}*/