#ifndef ACTION_H
#define ACTION_H

#include <string>

enum ActionType { WAIT, GRABBER, MOVE, TURN, UNKNOWN };

struct Action {
    ActionType type = UNKNOWN;
    std::string arguments = "";
    float target_x = 0.0;
    float target_y = 0.0;
    float angle = 0.0;
    std::string grabber_state = "";
    int timeout_s = 0;
};

#endif  // ACTION_H