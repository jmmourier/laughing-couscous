#include <gtest/gtest.h>

#include "Posi.h"
#include "PositionOrientation.h"

double const DOUBLE_NEAR_FACTOR = 0.001;

float const complete_tour = 0.628;

TEST(PosiTest, whenGettingNewTicks_absolutePositionShouldBeUpdatedAccordingly) {
    PositionOrientation start_position_orientation(0, 0, 0);

    auto posi = std::make_shared<Posi>(start_position_orientation);

    // Left wheel should make a full rotation while right wheel a bit less where
    // the final position expected contains an orientation_rad != 0
    posi->updatePosition(360, 360);

    auto position_orientation_ = posi->getPosition();

    EXPECT_NEAR(position_orientation_.x_m_, complete_tour, DOUBLE_NEAR_FACTOR);
    EXPECT_NEAR(position_orientation_.y_m_, 0, DOUBLE_NEAR_FACTOR);
}

TEST(PosiTest, whenGettingNewTicks2_absolutePositionShouldBeUpdatedAccordingly) {
    PositionOrientation start_position_orientation(0, 0, 0);

    auto posi = std::make_shared<Posi>(start_position_orientation);

    // Left wheel should make a full rotation while right wheel a bit less where
    // the final position expected contains an orientation_rad != 0
    posi->updatePosition(180, 180);

    auto position_orientation_ = posi->getPosition();

    EXPECT_NEAR(position_orientation_.x_m_, complete_tour / 2, DOUBLE_NEAR_FACTOR);
    EXPECT_NEAR(position_orientation_.y_m_, 0, DOUBLE_NEAR_FACTOR);
}