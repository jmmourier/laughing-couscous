#include "Posi.h"
#include <cmath>

const int TICKS_PER_ROTATION = 360;
const double SPACE_BETWEEN_WHEELS = 0.2;
const double WHEEL_RADIUS_M = 0.1;
const double WHEEL_PERIMETER = M_PI * 2 * WHEEL_RADIUS_M;

Posi::Posi(double &start_pos_x, double &start_pos_y, double &start_orientation)
    : abs_pos_x_(start_pos_x), abs_pos_y_(start_pos_y),
      orientation_(start_orientation),
      timestamp_(std::chrono::system_clock::now()) {}

void Posi::getPosition(double &pos_x, double &pos_y,
                       double &orientation) const {}

void Posi::updatePosition(int encoder1, int encoder2) {}
