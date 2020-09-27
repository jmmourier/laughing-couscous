#include "Posi.h"
#include <cmath>

const int TICKS_PER_ROTATION = 360;
const double SPACE_BETWEEN_WHEELS = 0.2;
const double WHEEL_RADIUS_M = 0.1;
const double WHEEL_PERIMETER = M_PI * 2 * WHEEL_RADIUS_M;

Posi::Posi(std::shared_ptr<IBaseTime> time_helper, double &start_pos_x,
           double &start_pos_y, double &start_orientation)
    : time_helper_(std::move(time_helper)), abs_pos_x_(start_pos_x),
      abs_pos_y_(start_pos_y), orientation_(start_orientation),
      timestamp_(time_helper_->getNow()) {}

void Posi::getPosition(double &pos_x, double &pos_y,
                       double &orientation) const {
  pos_x = abs_pos_x_;
  pos_y = abs_pos_y_;
  orientation = orientation_;
}

void Posi::updatePosition(int encoder1, int encoder2) {

  auto time_now = time_helper_->getNow();

  // Diff since last updating position in second
  auto delta_time_s =
      time_helper_->getDeltaTimeMS(time_now - timestamp_) / 1000;

  // Reset timestamp
  timestamp_ = time_now;

  // Convert ticks into angular speed
  double speed_left_wheel_radps =
      (WHEEL_PERIMETER * encoder1 / TICKS_PER_ROTATION);
  double speed_right_wheel_radps =
      (WHEEL_PERIMETER * encoder2 / TICKS_PER_ROTATION);

  // Linear speed
  double speed_left_wheel_ms = WHEEL_RADIUS_M * speed_left_wheel_radps;
  double speed_right_wheel_ms = WHEEL_RADIUS_M * speed_right_wheel_radps;

  // Average speed
  double average_speed = (speed_left_wheel_ms + speed_right_wheel_ms) / 2;

  // Delta positions
  double delta_position_x = std::cos(orientation_) * average_speed;
  double delta_position_y = std::sin(orientation_) * average_speed;

  // Delta orientation
  double delta_orientation =
      (speed_left_wheel_ms - speed_right_wheel_ms) / SPACE_BETWEEN_WHEELS;

  // Set new absolute positions and orientation
  abs_pos_x_ = abs_pos_x_ + delta_position_x * delta_time_s;
  abs_pos_y_ = abs_pos_y_ + delta_position_y * delta_time_s;
  orientation_ = orientation_ + delta_orientation * delta_time_s;
}