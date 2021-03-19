
#ifndef POSITION_H
#define POSITION_H

struct Position {
    Position(float x_m, float y_m) : x_m_(x_m), y_m_(y_m) {}
    float x_m_;
    float y_m_;
};

#endif  // POSITION_H