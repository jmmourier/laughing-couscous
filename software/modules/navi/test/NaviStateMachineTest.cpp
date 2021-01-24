#include <gtest/gtest.h>
#include <NaviStateMachine.h>
#include <cmath>
void dummy_lambda(int motor1, int motor2 ){

}
TEST(NaviStateMachineTest, start_align_to_target_1){
    pos_info robot_pos, target_pos;
    robot_pos.pos_x=0.0;
    robot_pos.pos_y=0.0;
    robot_pos.orientation=0.0;
    robot_pos.pos_x=1.0;
    robot_pos.pos_y=1.0;
    robot_pos.orientation=1.0;
    EXPECT_EQ(enumNaviStateMachine::ST2_ALIGN_TO_TARGET, state1_start_align_to_target(robot_pos, target_pos, dummy_lambda));
}

TEST(NaviStateMachineTest, align_to_target_2){
    pos_info robot_pos, target_pos;
    //anticlockwise
    robot_pos.pos_x=0.0;
    robot_pos.pos_y=0.0;
    robot_pos.orientation=0.0;
    target_pos.pos_x=1.0;
    target_pos.pos_y=1.0;
    target_pos.orientation=1.0;
    //turning in progress
    EXPECT_EQ(enumNaviStateMachine::ST2_ALIGN_TO_TARGET, state2_align_to_target(robot_pos, target_pos, dummy_lambda));
    //turning done
    robot_pos.orientation=M_PI/4;
    EXPECT_EQ(enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT, state2_align_to_target(robot_pos, target_pos, dummy_lambda));

    //clockwise
    robot_pos.orientation=M_PI/4+1;
    EXPECT_EQ(enumNaviStateMachine::ST2_ALIGN_TO_TARGET, state2_align_to_target(robot_pos, target_pos, dummy_lambda));
    robot_pos.orientation=M_PI/4;
    EXPECT_EQ(enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT, state2_align_to_target(robot_pos, target_pos, dummy_lambda));
}

TEST(NaviStateMachineTest, driving_to_target_5){
    pos_info robot_pos, target_pos;
    robot_pos.pos_x=0.0;
    robot_pos.pos_y=0.0;
    robot_pos.orientation=0.0;
    target_pos.pos_x=1.0;
    target_pos.pos_y=1.0;
    target_pos.orientation=1.0;
    //target not reached
    EXPECT_EQ(enumNaviStateMachine::ST5_DRIVING_TO_TARGET, state5_driving_to_target(robot_pos, target_pos, dummy_lambda));
    //target reached
    robot_pos.pos_x=target_pos.pos_x-(DELTA_DIST_TO_STOP_FW_MOVEMENT/1.42);
    robot_pos.pos_y=target_pos.pos_y-(DELTA_DIST_TO_STOP_FW_MOVEMENT/1.42);
    EXPECT_EQ(enumNaviStateMachine::ST6_WAIT_FOR_ROTATION,
              state5_driving_to_target(robot_pos, target_pos, dummy_lambda));
}

TEST(NaviStateMachineTest, rotation_to_target_orientation_8){
    pos_info robot_pos, target_pos;
    robot_pos.pos_x=0.0;
    robot_pos.pos_y=0.0;
    robot_pos.orientation=0.0;
    target_pos.pos_x=1.0;
    target_pos.pos_y=1.0;
    target_pos.orientation=1.0;
    //turning in progress
    EXPECT_EQ(enumNaviStateMachine::ST8_ROTATION_TO_TARGET_ORIENTATION,state8_rotation_to_target_orientation(robot_pos, target_pos));
    //turning done
    robot_pos.orientation=1.0;
    EXPECT_EQ(enumNaviStateMachine::ST9_DONE, state8_rotation_to_target_orientation(robot_pos, target_pos));
}