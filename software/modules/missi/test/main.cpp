#include <iostream>

#include "Missi.h"

int main(int argc, char *argv[]) {
    Missi mission;
    if (argc > 1) {
        mission.setMissionFilePath(argv[1]);
    }
    mission.loadMissionFile();

    Action action_to_print;
    for (int i = 0; i < 10; i++) {
        action_to_print = mission.getCurrentAction();
        std::cout << "Action : " << i
                  << "|action type : " << mission.actionTypeToString(action_to_print.type)
                  << "|argument : " << action_to_print.arguments
                  << "|target x : " << action_to_print.target_x
                  << "|target y : " << action_to_print.target_y
                  << "|angle : " << action_to_print.angle
                  << "|grabber : " << action_to_print.grabber_state
                  << "|timeout : " << action_to_print.timeout_s
                  << "|backward_distance : " << action_to_print.backward_distance << std::endl;
        mission.actionHasBeenDone();
    }

    return 0;
}