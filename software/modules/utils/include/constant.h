#ifndef CONSTANT_H
#define CONSTANT_H

#include <cmath>

namespace constant {
static const float wheel_diameter_m_ = 0.100;
static const float wheel_distance_m_ = 0.253;
static const float max_wheel_speed_radps_ = 17.802;  // 170 rpm <> 17,802 radps
static const int ticks_per_rotation = 360;
static const float whole_rotation_rad = M_PI * 2;
static const float wheel_perimeter_m = whole_rotation_rad * wheel_diameter_m_ / 2;
}  // namespace constant

#endif  // CONSTANT_H