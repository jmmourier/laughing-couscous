
#ifndef POSITIONORIENTATION_H
#define POSITIONORIENTATION_H

#include "Position.h"

struct PositionOrientation : public Position {
    PositionOrientation(float x_m, float y_m, float orientation_rad)
        : Position(x_m, y_m),
          orientation_rad_(orientation_rad) {}
    float orientation_rad_;
};

#endif  // POSITIONORIENTATION_H