#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>

enum ActionType { WAIT, GRIPPER, MOVE, TURN };

struct Action {
    ActionType type;
    std::vector<std::string> arguments;
};

#endif  // ACTION_H