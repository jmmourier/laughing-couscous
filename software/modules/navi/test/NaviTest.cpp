#include "Navi.h"
#include "NaviUtils.h"
#include <cmath>
#include <gtest/gtest.h>

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
    //std::cout<<"get state:"<<nav.getActualState()<<std::endl;
    nav.setCurrentPosition(rob_start_position.pos_x, rob_start_position.pos_y, rob_start_position.orientation);
    nav.setTargetPosition(target_position.pos_x, target_position.pos_y, target_position.orientation);
    //std::cout<<"get state:"<<nav.getActualState()<<std::endl;
    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);
    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);
    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);
    //std::cout<<"target..."<<rob_point_aligned_to_target.pos_x<<" "<<rob_point_aligned_to_target.pos_y<<" "<<target_position.pos_x<<" "<<target_position.pos_y<<std::endl;
    double dist = get_distance_to_target(rob_point_aligned_to_target, target_position);
    //std::cout<<"distance..."<<dist<<std::endl;
    nav.setCurrentPosition(rob_point_aligned_to_target.pos_x, rob_point_aligned_to_target.pos_y, rob_point_aligned_to_target.orientation);
    nav.setCurrentPosition(rob_point2.pos_x, rob_point2.pos_y, rob_point2.orientation);
    nav.setCurrentPosition(rob_end_position.pos_x, rob_end_position.pos_y, rob_end_position.orientation);
    nav.setCurrentPosition(rob_end_position.pos_x, rob_end_position.pos_y, rob_end_position.orientation);
    nav.setCurrentPosition(rob_end_position.pos_x, rob_end_position.pos_y, rob_end_position.orientation);
    nav.setCurrentPosition(rob_end_position.pos_x, rob_end_position.pos_y, rob_end_position.orientation);

}
