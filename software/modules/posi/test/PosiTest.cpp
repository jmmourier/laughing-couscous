#include <gtest/gtest.h>

#include "FakeTime.h"
#include "Posi.h"
#include "PositionOrientation.h"

double const DOUBLE_NEAR_FACTOR = 0.00001;

TEST(PosiTest, whenGettingNewTicks_absolutePositionShouldBeUpdatedAccordingly) {
    PositionOrientation start_position_orientation(0, 0, 0);

    // Simulates a delta time of 1000 ms
    auto time_helper = std::make_shared<FakeTime>(1000);

    auto posi = std::make_shared<Posi>(time_helper, start_position_orientation);

    // Left wheel should make a full rotation while right wheel a bit less where
    // the final position expected contains an orientation_rad != 0
    posi->updatePosition(360, -200);

    auto position_orientation_ = posi->getPosition();

    EXPECT_NEAR(position_orientation_.x_m_, 0.13962, DOUBLE_NEAR_FACTOR);
    EXPECT_NEAR(position_orientation_.y_m_, 0, DOUBLE_NEAR_FACTOR);
    EXPECT_NEAR(position_orientation_.orientation_rad_, 4.88692, DOUBLE_NEAR_FACTOR);
}

TEST(PosiTest, whenPositionUpdatedMultipleTimes_absolutePositionShouldBeUpdatedAccordingly) {
    PositionOrientation start_position_orientation(0, 0, 0);

    // Simulates a delta time of 1000 ms
    auto time_helper = std::make_shared<FakeTime>(1000);

    auto posi = std::make_shared<Posi>(time_helper, start_position_orientation);

    // Position updated twice to check if the previous ticks where taken into
    // account
    posi->updatePosition(360, 360);
    posi->updatePosition(720, 720);  // Same speed so 360 * 2

    auto position_orientation_ = posi->getPosition();

    EXPECT_NEAR(position_orientation_.x_m_, 1.25663, DOUBLE_NEAR_FACTOR);
    EXPECT_NEAR(position_orientation_.y_m_, 0, DOUBLE_NEAR_FACTOR);
    EXPECT_NEAR(position_orientation_.orientation_rad_, 0, DOUBLE_NEAR_FACTOR);
}