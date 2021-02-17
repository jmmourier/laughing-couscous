#include "Missi.h"
#include "json.hpp"

#include <string>
#include <fstream>
#include <iostream>

Missi::Missi() : mission_file_path_("mission.json"), previous_action_has_been_done_(false), next_action_indice_(0) {
    current_action_.type = WAIT;
    current_action_.arguments = "Waiting to start";
    current_action_.timeout_s = 0;
}

void Missi::setMissionFilePath(std::string mission_file_path){
    mission_file_path_ = mission_file_path;
}

void Missi::loadMissionFile() {
    // create an empty structure (null)
    nlohmann::json json_content;
    
    // load file
    std::ifstream file_stream(mission_file_path_);
    try
    {
        file_stream >> json_content;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    for (nlohmann::json::iterator it = json_content.begin(); it != json_content.end(); ++it) {
        nlohmann::json action_as_json(*it);
        Action action_to_add;
        action_to_add.type = stringToActionType(action_as_json["actionType"]);
        action_to_add.arguments = action_as_json["arguments"];
        try
        {
            std::string timeout_as_string = action_as_json["timeout"];
            action_to_add.timeout_s = std::stoi(timeout_as_string);
        }
        catch(const std::exception& e)
        {   
            std::cerr << "Wrong timeout value conversion" << std::endl;
            action_to_add.timeout_s = 0;
        }
        action_list_.emplace_back(action_to_add);
    }
    std::cout << "[Mission] " << action_list_.size() << " actions have been added from file" << std::endl; 

}

void Missi::actionHasBeenDone() {
    previous_action_has_been_done_ = true;
}

Action Missi::getCurrentAction() {
    if (previous_action_has_been_done_ == true && 
        !action_list_.empty()) {
            if(action_list_.size() <= next_action_indice_){
                // no more action
                current_action_.type = WAIT;
                current_action_.arguments = "mission done";
                current_action_.timeout_s = 0; 
            }
            else {
                current_action_ = action_list_.at(next_action_indice_);
                next_action_indice_ ++;
            }
        previous_action_has_been_done_ = false;
    }
    return current_action_;
}


ActionType Missi::stringToActionType(std::string action_type_as_string){
    if(!action_type_as_string.compare("wait")) return WAIT;
    if(!action_type_as_string.compare("grabber")) return GRABBER;
    if(!action_type_as_string.compare("move")) return MOVE;
    if(!action_type_as_string.compare("turn")) return TURN;
    return UNKNOWN;
}

std::string Missi::actionTypeToString(ActionType action_type){
    if(action_type == WAIT) return "wait";
    if(action_type == GRABBER) return "grabber";
    if(action_type == MOVE) return "move";
    if(action_type == TURN) return "turn";
    if(action_type == UNKNOWN) return "unknown";
    return "unknown";
}
