#ifndef POSI_H
#define POSI_H

#include <chrono>

class Posi {
public:
  Posi(double &start_pos_x, double &start_pos_y, double &start_orientation);

  /**
   * @brief Return abs position and orientation
   *
   * @param pos_x
   * @param pos_y
   * @param orientation
   */
  void getPosition(double &pos_x, double &pos_y, double &orientation) const;

  /**
   * @brief Update the absolute position and orientation based on new encoders
   * value received from hali moodule
   *
   * @param encoder1 encoders of left wheel since last update
   * @param encoder2 encoders of right wheel since last update
   */
  void updatePosition(int encoder1, int encoder2);

private:
  double abs_pos_x_;
  double abs_pos_y_;
  double orientation_;
  std::chrono::_V2::system_clock::time_point timestamp_;
};

#endif // POSI_H
