#include "Missi.h"

Missi::Missi() : 
mission_file_path("."),
mission_color_(BLUE),
previous_action_has_been_done_(false){
    loadMissionFile();
    current_action.type = WAIT;
    current_action.arguments.clear();
}

void Missi::setMissionColor(MissionColor mission_color){
    mission_color_ = mission_color;
}

void Missi::loadMissionFile(){
    //blue_mission_ = ...;
    //yellow_mission_ = ...;
}

void Missi::actionHasBeenDone(bool action_done){
    previous_action_has_been_done_ = action_done;
}

Action Missi::getCurrentAction(){
    if(previous_action_has_been_done_ == true){
        //replace that by reading the next action in the list
        current_action.type = GRIPPER;
        current_action.arguments.clear();
        current_action.arguments.emplace_back("0");

        previous_action_has_been_done_ = false;
    }
    return current_action;
}