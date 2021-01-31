#ifndef MISSI_H
#define MISSI_H

#include <string>

#include "Action.h"

enum MissionColor { BLUE, YELLOW };

class Missi {
   private:
    void loadMissionFile();
    std::string mission_file_path;
    MissionColor mission_color_;
    bool previous_action_has_been_done_;

    Action current_action;

   public:
    Missi();
    void setMissionColor(MissionColor mission_color);

    void actionHasBeenDone(bool action_done);
    Action getCurrentAction();
};

#endif  // MISSI_H