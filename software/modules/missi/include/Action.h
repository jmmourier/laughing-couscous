#ifndef ACTION_H
#define ACTION_H

#include <string>

#include "Types.h"

struct Action {
    ActionType type = UNKNOWN;
    std::string arguments = "";
    float target_x = 0.0;
    float target_y = 0.0;
    float angle = 0.0;
    bool hasActionStarted = false;
    std::string grabber_state = "";
    float backward_distance = 0.0;
    float forward_distance = 0.0;
    int timeout_s = 0;
};

#endif  // ACTION_H