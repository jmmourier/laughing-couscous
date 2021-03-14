#include <gtest/gtest.h>

#include <cmath>

#include "NaviUtils.h"

#define ANGLE_ERROR_TOLERANCE 0.001

TEST(NaviUtilsTest, compute_angle_with_reference) {
    double robot_pos_x;
    double robot_pos_y;
    double target_pos_x;
    double target_pos_y;

    // quarter 1: x pos and y pos
    robot_pos_x = 0.0;
    robot_pos_y = 0.0;
    target_pos_x = 100.0;
    target_pos_y = 100.0;
    double angle = getReferenceAngleToTarget(robot_pos_x, robot_pos_y, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, M_PI / 4, ANGLE_ERROR_TOLERANCE);

    // quarter 2: x neg and y pos
    robot_pos_x = 100.0;
    robot_pos_y = 0.0;
    target_pos_x = 0.0;
    target_pos_y = 100.0;
    angle = getReferenceAngleToTarget(robot_pos_x, robot_pos_y, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, (3.f / 4.f) * M_PI, ANGLE_ERROR_TOLERANCE);

    // quarter 3: x neg and y neg
    robot_pos_x = 100.0;
    robot_pos_y = 100.0;
    target_pos_x = 0.0;
    target_pos_y = 0.0;
    angle = getReferenceAngleToTarget(robot_pos_x, robot_pos_y, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, M_PI + (M_PI / 4.f), ANGLE_ERROR_TOLERANCE);

    // quarter 4: x pos and y neg
    robot_pos_x = 0.0;
    robot_pos_y = 100.0;
    target_pos_x = 100.0;
    target_pos_y = 0.0;
    angle = getReferenceAngleToTarget(robot_pos_x, robot_pos_y, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, M_PI + ((3.f / 4.f) * M_PI), ANGLE_ERROR_TOLERANCE);

    robot_pos_x = 100.0;
    robot_pos_y = 100.0;
    target_pos_x = 200.0;
    target_pos_y = 200.0;
    angle = getReferenceAngleToTarget(robot_pos_x, robot_pos_y, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, M_PI / 4, ANGLE_ERROR_TOLERANCE);
}

TEST(NaviUtilsTest, compute_angle_with_target) {
    double robot_pos_x;
    double robot_pos_y;
    double robot_orientation;
    double target_pos_x;
    double target_pos_y;

    // quarter 1: x pos and y pos
    robot_pos_x = 0.0;
    robot_pos_y = 0.0;
    robot_orientation = 0.0;
    target_pos_x = 100.0;
    target_pos_y = 100.0;
    double angle =
        getAngleToTarget(robot_pos_x, robot_pos_y, robot_orientation, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, M_PI / 4, ANGLE_ERROR_TOLERANCE);

    robot_orientation = M_PI / 4;
    angle =
        getAngleToTarget(robot_pos_x, robot_pos_y, robot_orientation, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, 0, ANGLE_ERROR_TOLERANCE);

    robot_orientation = M_PI;
    angle =
        getAngleToTarget(robot_pos_x, robot_pos_y, robot_orientation, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, -3 * (M_PI / 4), ANGLE_ERROR_TOLERANCE);

    robot_orientation = M_PI + (M_PI / 4);
    angle =
        getAngleToTarget(robot_pos_x, robot_pos_y, robot_orientation, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, -M_PI, ANGLE_ERROR_TOLERANCE);

    // quarter 2: x neg and y pos
    robot_pos_x = 100.0;
    robot_pos_y = 0.0;
    target_pos_x = 0.0;
    target_pos_y = 100.0;
    robot_orientation = 0.0;
    angle =
        getAngleToTarget(robot_pos_x, robot_pos_y, robot_orientation, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, (3.f / 4.f) * M_PI, ANGLE_ERROR_TOLERANCE);

    // quarter 3: x neg and y neg
    robot_pos_x = 100.0;
    robot_pos_y = 100.0;
    target_pos_x = 0.0;
    target_pos_y = 0.0;
    robot_orientation = 0.0;
    angle =
        getAngleToTarget(robot_pos_x, robot_pos_y, robot_orientation, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, 3 * (M_PI / 4.f), ANGLE_ERROR_TOLERANCE);

    // quarter 4: x pos and y neg
    robot_pos_x = 0.0;
    robot_pos_y = 100.0;
    target_pos_x = 100.0;
    target_pos_y = 0.0;
    robot_orientation = 0.0;
    angle =
        getAngleToTarget(robot_pos_x, robot_pos_y, robot_orientation, target_pos_x, target_pos_y);
    EXPECT_NEAR(angle, M_PI / 4.f, ANGLE_ERROR_TOLERANCE);
}

TEST(NaviUtilsTest, utils_rotation_direction) {
    // case: robot_orientation > target_orientation. diff<PI
    EXPECT_EQ(rotation_direction::Clockwise, getRotationDirection(3 * (M_PI / 4.f), M_PI / 4.f));

    // case: robot_orientation < target_orientation. diff<PI
    EXPECT_EQ(
        rotation_direction::AntiClockwise,
        getRotationDirection(M_PI / 4.f, 3 * (M_PI / 4.f)));

    // case: robot_orientation > target_orientation. diff > PI
    EXPECT_EQ(rotation_direction::Clockwise, getRotationDirection(M_PI + (M_PI / 3.f), M_PI / 2.f));
    // case: robot_orientation < target_orientation. diff > PI
    EXPECT_EQ(
        rotation_direction::AntiClockwise,
        getRotationDirection(M_PI / 3.f, M_PI + 3 * (M_PI / 4.f)));
    // case: identical angles
    EXPECT_EQ(rotation_direction::Clockwise, getRotationDirection(M_PI, M_PI));
}

TEST(NaviUtilsTest, utils_test_angles_diff) {
    // case 1
    double robot_orientation = 3 * (M_PI / 4);
    double target_orientation = M_PI / 4;
    double rotation_angle = getAngleDifference(robot_orientation, target_orientation);
    EXPECT_FLOAT_EQ(rotation_angle, -M_PI / 2);

    // case 2
    robot_orientation = M_PI / 4;
    target_orientation = 3 * (M_PI / 4);
    rotation_angle = getAngleDifference(robot_orientation, target_orientation);
    EXPECT_FLOAT_EQ(rotation_angle, M_PI / 2);

    // case 3: angle exceed PI
    robot_orientation = 7 * (M_PI / 4);
    target_orientation = M_PI / 4;
    rotation_angle = getAngleDifference(robot_orientation, target_orientation);
    //  std::cout<<"----"<<rotation_angle<<std::endl;
    EXPECT_FLOAT_EQ(rotation_angle, M_PI / 2);
}

TEST(NaviUtilsTest, distance_computation) {
    pos_info p1, p2, p3;
    p1.pos_x = 0.0;
    p1.pos_y = 0.0;
    p2.pos_x = 100.0;
    p2.pos_y = 100.0;
    p3.pos_x = 0.0;
    p3.pos_y = 100.0;
    EXPECT_FLOAT_EQ(getDistanceToTarget(p1, p2), 141.421356237);
    EXPECT_FLOAT_EQ(getDistanceToTarget(p1, p3), 100.0);
}