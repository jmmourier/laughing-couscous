#include "Moti.h"

#include <algorithm>
#include <iostream>

Moti::Moti() {}

MotorSpeed Moti::getMotorSpeedFromBaseSpeed(BaseSpeed base_speed) {
    MotorSpeed motor_speed(127, 127);

    float rotation_speed_left = 0.0;
    float rotation_speed_right = 0.0;

    // add linar speed
    rotation_speed_left += base_speed.v_x_mps_;
    rotation_speed_right += base_speed.v_x_mps_;

    // add rotation
    rotation_speed_left -= base_speed.omega_radps_ * wheel_distance_m_ / 2.0;
    rotation_speed_right += base_speed.omega_radps_ * wheel_distance_m_ / 2.0;

    // convert to motor speed
    rotation_speed_left = rotation_speed_left / (wheel_diameter_m_ / 2.0);
    rotation_speed_right = rotation_speed_right / (wheel_diameter_m_ / 2.0);

    // capping values
    rotation_speed_left = std::min(rotation_speed_left, max_wheel_speed_radps_);
    rotation_speed_left = std::max(rotation_speed_left, -max_wheel_speed_radps_);
    rotation_speed_right = std::min(rotation_speed_right, max_wheel_speed_radps_);
    rotation_speed_right = std::max(rotation_speed_right, -max_wheel_speed_radps_);

    // convert motor speed to command
    motor_speed.speed_motor_1_ = 127 + 127 * rotation_speed_left / max_wheel_speed_radps_;
    motor_speed.speed_motor_2_ = 127 + 127 * rotation_speed_right / max_wheel_speed_radps_;

    return motor_speed;
}
