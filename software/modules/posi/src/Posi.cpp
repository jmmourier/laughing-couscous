#include "Posi.h"

Posi::Posi(double &start_pos_x, double &start_pos_y, double &start_orientation)
    : abs_pos_x_(start_pos_x), abs_pos_y_(start_pos_y),
      orientation_(start_orientation),
      timestamp_(std::chrono::system_clock::now()) {}

void Posi::getPosition(double &pos_x, double &pos_y,
                       double &orientation) const {}

void Posi::updatePosition(int encoder1, int encoder2) {}
