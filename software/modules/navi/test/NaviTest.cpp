#include "Navi.h"
#include "NaviUtils.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(NaviTest, standard_path){
    pos_info target_position, rob_start_position, rob_point_aligned_to_target, rob_point2, rob_end_position;
    rob_start_position.pos_x=0.0;
    rob_start_position.pos_y=0.0;
    rob_start_position.orientation=0.0;

    rob_point_aligned_to_target.pos_x=0.1;
    rob_point_aligned_to_target.pos_y=0.1;
    rob_point_aligned_to_target.orientation=M_PI/4.0;

    rob_point2.pos_x=0.2;
    rob_point2.pos_y=0.2;
    rob_point2.orientation=0.0;

    rob_end_position.pos_x=1.0;
    rob_end_position.pos_y=1.0;
    rob_end_position.orientation=0.0;

    target_position.pos_x=1.0;
    target_position.pos_y=1.0;
    target_position.orientation=0.0;

    Navi nav;
    EXPECT_EQ(enumNaviStateMachine::ST0_IDLE, nav.getActualState());
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, rob_start_position.orientation);
    EXPECT_EQ(enumNaviStateMachine::ST0_IDLE, nav.getActualState());

    nav.setTargetPosition(target_position.pos_x, target_position.pos_y, target_position.orientation);
    EXPECT_EQ(enumNaviStateMachine::ST1_START_ALIGN_TO_TARGET, nav.getActualState());
//rotate to target
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, rob_start_position.orientation);
    EXPECT_EQ(enumNaviStateMachine::ST2_ALIGN_TO_TARGET, nav.getActualState());
//still in rotation
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, rob_start_position.orientation);
    EXPECT_EQ(enumNaviStateMachine::ST2_ALIGN_TO_TARGET, nav.getActualState());
//rotation done



    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);

}
/*
TEST(NaviTest, state_machine_test){
    pos_info target_position, rob_start_position, rob_point_aligned_to_target, rob_point2, rob_end_position;
    rob_start_position.pos_x=0.0;
    rob_start_position.pos_y=0.0;
    rob_start_position.orientation=0.0;
    rob_point_aligned_to_target.pos_x=0.1;
    rob_point_aligned_to_target.pos_y=0.1;
    rob_point_aligned_to_target.orientation=M_PI/4.0;
    rob_point2.pos_x=0.2;
    rob_point2.pos_y=0.2;
    rob_point2.orientation=0.0;
    rob_end_position.pos_x=1.0;
    rob_end_position.pos_y=1.0;
    rob_end_position.orientation=0.0;

    target_position.pos_x=1.0;
    target_position.pos_y=1.0;
    target_position.orientation=0.0;

    Navi nav;
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, rob_start_position.orientation);
    nav.setTargetPosition(target_position.pos_x, target_position.pos_y, target_position.orientation);
    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);
    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);
    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);
    double dist = get_distance_to_target(rob_point_aligned_to_target, target_position);
    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);
    nav.setCurrentPosition(rob_point2.pos_x, rob_point2.pos_y, rob_point2.orientation);
    nav.setCurrentPosition(rob_end_position.pos_x, rob_end_position.pos_y, rob_end_position.orientation);
    nav.setCurrentPosition(rob_end_position.pos_x, rob_end_position.pos_y, rob_end_position.orientation);
    nav.setCurrentPosition(rob_end_position.pos_x, rob_end_position.pos_y, rob_end_position.orientation);
    nav.setCurrentPosition(rob_end_position.pos_x, rob_end_position.pos_y, rob_end_position.orientation);

}
*/