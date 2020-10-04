#include "Posi.h"
#include "FakeTime.h"
#include <gtest/gtest.h>

double const DOUBLE_NEAR_FACTOR = 0.00001;

TEST(PosiTest, whenGettingNewTicks_absolutePositionShouldBeUpdatedAccordingly) {
  double start_pox_x_m = 0;
  double start_pos_y_m = 0;
  double orientation_rad = 0;

  // Simulates a delta time of 1000 ms
  auto time_helper = std::make_shared<FakeTime>(1000);

  auto posi = std::make_shared<Posi>(time_helper, start_pox_x_m, start_pos_y_m,
                                     orientation_rad);

  // Left wheel should make a full rotation while right wheel a bit less where
  // the final position expected contains an orientation_rad != 0
  posi->updatePosition(360, -200);

  double new_abs_pos_x_m = 0;
  double new_abs_pos_y_m = 0;
  double new_abs_orientation_rad = 0;

  posi->getPosition(new_abs_pos_x_m, new_abs_pos_y_m, new_abs_orientation_rad);

  EXPECT_NEAR(new_abs_pos_x_m, 0.13962, DOUBLE_NEAR_FACTOR);
  EXPECT_NEAR(new_abs_pos_y_m, 0, DOUBLE_NEAR_FACTOR);
  EXPECT_NEAR(new_abs_orientation_rad, 4.88692, DOUBLE_NEAR_FACTOR);
}

TEST(
    PosiTest,
    whenPositionUpdatedMultipleTimes_absolutePositionShouldBeUpdatedAccordingly) {

  double start_pox_x_m = 0;
  double start_pos_y_m = 0;
  double orientation_rad = 0;

  // Simulates a delta time of 1000 ms
  auto time_helper = std::make_shared<FakeTime>(1000);

  auto posi = std::make_shared<Posi>(time_helper, start_pox_x_m, start_pos_y_m,
                                     orientation_rad);

  // Position updated twice to check if the previous ticks where taken into
  // account
  posi->updatePosition(360, 360);
  posi->updatePosition(720, 720); // Same speed so 360 * 2

  double new_abs_pos_x_m = 0;
  double new_abs_pos_y_m = 0;
  double new_abs_orientation_rad = 0;

  posi->getPosition(new_abs_pos_x_m, new_abs_pos_y_m, new_abs_orientation_rad);

  EXPECT_NEAR(new_abs_pos_x_m, 1.25663, DOUBLE_NEAR_FACTOR);
  EXPECT_NEAR(new_abs_pos_y_m, 0, DOUBLE_NEAR_FACTOR);
  EXPECT_NEAR(new_abs_orientation_rad, 0, DOUBLE_NEAR_FACTOR);
}