#ifndef ACTION_H
#define ACTION_H

#include <string>

enum ActionType { WAIT, GRABBER, MOVE, TURN, UNKNOWN };

struct Action {
    ActionType type;
    std::string arguments;
    int timeout_s = 0;
};

#endif  // ACTION_H