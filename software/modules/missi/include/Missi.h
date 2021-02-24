#ifndef MISSI_H
#define MISSI_H

#include <string>
#include <vector>

#include "Action.h"

class Missi {
   private:
    std::string mission_file_path_;
    bool previous_action_has_been_done_;

    Action current_action_;
    int next_action_indice_;
    std::vector<Action> action_list_;

    ActionType stringToActionType(std::string action_type_as_string);
    std::string actionTypeToString(ActionType action_type);

   public:
    Missi();
    void loadMissionFile();
    void setMissionFilePath(std::string mission_file_path);

    void actionHasBeenDone();
    Action getCurrentAction();
};

#endif  // MISSI_H