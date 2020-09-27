#include "Posi.h"
#include "FakeTime.h"
#include <cmath>
#include <iostream>

int main(int argc, char *argv[]) {
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

  double expected_new_abs_pos_x = 1.01396;
  double expected_new_abs_pos_y = 1;
  double expected_new_abs_pos_orientation = 0.488692;

  std::cout << "Abs position X: " << new_abs_pos_x << std::endl;
  std::cout << "Abs position Y: " << new_abs_pos_y << std::endl;
  std::cout << "Abs position Orientation: " << new_abs_orientation << std::endl;

  if (std::fabs(new_abs_pos_x - expected_new_abs_pos_x) > 0.0001 ||
      std::fabs(new_abs_pos_y - expected_new_abs_pos_y) > 0.0001 ||
      std::fabs(new_abs_orientation - expected_new_abs_pos_orientation) >
          0.0001) {
    std::cout << "WRONT RESULTS !! Expected results are:" << std::endl;
    std::cout << "Expected abs position X: " << expected_new_abs_pos_x
              << std::endl;
    std::cout << "Expected abs position Y: " << expected_new_abs_pos_y
              << std::endl;
    std::cout << "Expected abs position Orientation: "
              << expected_new_abs_pos_orientation << std::endl;
  } else {
    std::cout << "SUCCESS !! Results are as expected" << std::endl;
  }

  return 0;
}