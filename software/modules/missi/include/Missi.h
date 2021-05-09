#ifndef MISSI_H
#define MISSI_H

#include <chrono>
#include <string>
#include <vector>

#include "Action.h"

class Missi {
   public:
    Missi();
    void loadMissionFile();
    void setMissionFilePath(std::string mission_file_path);

    void actionHasBeenDone();
    Action getCurrentAction();

    std::string actionTypeToString(ActionType action_type);

   private:
    std::string mission_file_path_;
    bool previous_action_has_been_done_;

    Action current_action_;
    std::chrono::_V2::system_clock::time_point timestamp_current_action_started_;

    int next_action_indice_;
    std::vector<Action> action_list_;

    ActionType stringToActionType(std::string action_type_as_string);
    bool hasCurrentActionTimeout();

};

#endif  // MISSI_H