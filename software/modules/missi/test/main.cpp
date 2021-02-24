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
        std::cout << "Action : " << i << std::endl;
        std::cout << action_to_print.type << " -- " << action_to_print.arguments << " -- "
                  << action_to_print.timeout_s << std::endl;
        mission.actionHasBeenDone();
    }

    return 0;
}