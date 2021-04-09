#include <gtest/gtest.h>

#include <cmath>

#include "Posi.h"
#include "PositionOrientation.h"
#include "constant.h"

double const DOUBLE_NEAR_FACTOR = 0.01;

TEST(PosiTest, whenGettingNewTicks_absoluteXPositionAWheelPermimeter) {
    PositionOrientation start_position_orientation(0, 0, 0);

    auto posi = std::make_shared<Posi>(start_position_orientation);

    // Left/Right wheels should make a full rotation
    posi->updatePosition(360, 360);

    auto position_orientation_ = posi->getPosition();

    EXPECT_NEAR(position_orientation_.x_m_, constant::wheel_perimeter_m, DOUBLE_NEAR_FACTOR);
    EXPECT_NEAR(position_orientation_.y_m_, 0, DOUBLE_NEAR_FACTOR);
}

TEST(PosiTest, whenGettingNewTicks_absoluteXPositionAWheelPermimeterAndAHalf) {
    PositionOrientation start_position_orientation(0, 0, 0);

    auto posi = std::make_shared<Posi>(start_position_orientation);

    // Left/Right wheels should make a rotation and a half
    posi->updatePosition(360, 360);  // full rotation
    posi->updatePosition(540, 540);  // full rotation + half rotation

    auto position_orientation_ = posi->getPosition();

    EXPECT_NEAR(position_orientation_.x_m_, constant::wheel_perimeter_m * 1.5, DOUBLE_NEAR_FACTOR);
    EXPECT_NEAR(position_orientation_.y_m_, 0, DOUBLE_NEAR_FACTOR);
}

TEST(PosiTest, whenGettingNewTicks_orientationShouldBeThreeQuarterOfATurn) {
    PositionOrientation start_position_orientation(0, 0, 0);

    float arc_perimeter_m = constant::whole_rotation_rad * constant::wheel_distance_m_ / 2;

    int ticks_for_quarter_arc_m = static_cast<int>(std::nearbyint(
        arc_perimeter_m / constant::wheel_perimeter_m * constant::ticks_per_rotation / 4));

    auto posi = std::make_shared<Posi>(start_position_orientation);

    // Robot should turn a quarter on itself clockwise
    posi->updatePosition(ticks_for_quarter_arc_m, -ticks_for_quarter_arc_m);  // half rotation

    auto position_orientation_ = posi->getPosition();

    EXPECT_NEAR(
        position_orientation_.orientation_rad_,
        constant::whole_rotation_rad / 4 * 3,
        DOUBLE_NEAR_FACTOR);
}