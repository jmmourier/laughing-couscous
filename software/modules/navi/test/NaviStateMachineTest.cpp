#include <gtest/gtest.h>
#include <NaviStateMachine.h>
#include <cmath>

TEST(NaviStateMachineTest, start_align_to_target_1){
    pos_info robot_pos, target_pos;
    robot_pos.pos_x=0.0;
    robot_pos.pos_y=0.0;
    robot_pos.orientation=0.0;
    robot_pos.pos_x=1.0;
    robot_pos.pos_y=1.0;
    robot_pos.orientation=1.0;
    EXPECT_EQ(enumNaviStateMachine::ST2_ALIGN_TO_TARGET, state1_start_align_to_target(robot_pos, target_pos));
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
    EXPECT_EQ(enumNaviStateMachine::ST2_ALIGN_TO_TARGET, state2_align_to_target(robot_pos, target_pos));
    //turning done
    robot_pos.orientation=M_PI/4;
    EXPECT_EQ(enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT, state2_align_to_target(robot_pos, target_pos));

    //clockwise
    robot_pos.orientation=M_PI/4+1;
    EXPECT_EQ(enumNaviStateMachine::ST2_ALIGN_TO_TARGET, state2_align_to_target(robot_pos, target_pos));
    robot_pos.orientation=M_PI/4;
    EXPECT_EQ(enumNaviStateMachine::ST3_WAIT_FOR_MOVMENT, state2_align_to_target(robot_pos, target_pos));


}

TEST(NaviStateMachineTest, driving_to_target){
    pos_info robot_pos, target_pos;
    robot_pos.pos_x=0.0;
    robot_pos.pos_y=0.0;
    robot_pos.orientation=0.0;
    target_pos.pos_x=1.0;
    target_pos.pos_y=1.0;
    target_pos.orientation=1.0;
    //target not reached
    EXPECT_EQ(enumNaviStateMachine::ST5_DRIVING_TO_TARGET, state5_driving_to_target(robot_pos, target_pos));
    //target reached
    robot_pos.pos_x=target_pos.pos_x-(DELTA_DIST_TO_STOP_FW_MOVEMENT/1.42);
    robot_pos.pos_y=target_pos.pos_y-(DELTA_DIST_TO_STOP_FW_MOVEMENT/1.42);
    EXPECT_EQ(enumNaviStateMachine::ST7_START_ROTATION_TO_TARGET_ORIENTATION,
              state5_driving_to_target(robot_pos, target_pos));
}

TEST(NaviStateMachineTest, rotation_to_target_orientation){
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