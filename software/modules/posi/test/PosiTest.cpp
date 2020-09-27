#include "Posi.h"
#include "FakeTime.h"
#include <cmath>
#include <gtest/gtest.h>

double const DOUBLE_NEAR_FACTOR = 0.00001;

TEST(PosiTest, whenGettingNewTicks_absolutePositionShouldBeUpdatedAccordingly) {
  double start_pox_x = 1;
  double start_pos_y = 1;
  double orientation = 0;

  // Simulates a delta time of 1000 ms
  auto time_helper = std::make_shared<FakeTime>(1000);

  auto posi = std::make_shared<Posi>(time_helper, start_pox_x, start_pos_y,
                                     orientation);

  // Left wheel should make a full rotation while right wheel a bit less where
  // the final position expected contains an orientation != 0
  posi->updatePosition(360, -200);

  double new_abs_pos_x = 0;
  double new_abs_pos_y = 0;
  double new_abs_orientation = 0;

  posi->getPosition(new_abs_pos_x, new_abs_pos_y, new_abs_orientation);

  EXPECT_NEAR(new_abs_pos_x, 1.01396, DOUBLE_NEAR_FACTOR);
  EXPECT_NEAR(new_abs_pos_y, 1, DOUBLE_NEAR_FACTOR);
  EXPECT_NEAR(new_abs_orientation, 0.48869, DOUBLE_NEAR_FACTOR);
}