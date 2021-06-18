#include "Missi.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Action.h"
#include "json.hpp"
#include "logger/LoggerFactory.h"

Missi::Missi()
    : logger_(LoggerFactory::registerOrGetLogger("Missi", spdlog::level::level_enum::info)),
      mission_file_path_(
          std::string(std::getenv("MISSION_PATH")).append("/").append("mission_yellow.json")),
      previous_action_has_been_done_(false),
      next_action_indice_(0) {
    current_action_.type = WAIT;
    current_action_.arguments = "Waiting to start";
    current_action_.timeout_s = 0;
    timestamp_current_action_started_ = std::chrono::system_clock::now();
}

void Missi::setMissionFilePath(std::string mission_file_path) {
    mission_file_path_ = mission_file_path;
}

void Missi::loadMissionFile() {
    // create an empty structure (null)
    nlohmann::json json_content;

    // load file
    std::ifstream file_stream(mission_file_path_);
    try {
        file_stream >> json_content;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    for (nlohmann::json::iterator it = json_content.begin(); it != json_content.end(); ++it) {
        nlohmann::json action_as_json(*it);
        Action action_to_add;
        try {
            action_to_add.type = stringToActionType(action_as_json["actionType"]);
            if (action_as_json.contains("arguments")) {
                action_to_add.arguments = action_as_json["arguments"];
            }
            if (action_as_json.contains("target_x")) {
                action_to_add.target_x = action_as_json["target_x"];
            }
            if (action_as_json.contains("target_y")) {
                action_to_add.target_y = action_as_json["target_y"];
            }
            if (action_as_json.contains("angle")) {
                action_to_add.angle = action_as_json["angle"];
            }
            if (action_as_json.contains("grabber_state")) {
                action_to_add.grabber_state = action_as_json["grabber_state"];
            }
            if (action_as_json.contains("timeout")) {
                action_to_add.timeout_s = action_as_json["timeout"];
            }
            if (action_as_json.contains("backward_distance")) {
                action_to_add.backward_distance = action_as_json["backward_distance"];
            }
            if (action_as_json.contains("forward_distance")) {
                action_to_add.forward_distance = action_as_json["forward_distance"];
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Wrong value conversion" << std::endl;
        }
        action_list_.emplace_back(action_to_add);
    }

    SPDLOG_LOGGER_INFO(logger_, "{} actions have been added from file", action_list_.size());

    for (int i = 0; i < action_list_.size(); i++) {
        SPDLOG_LOGGER_INFO(
            logger_,
            "Action {} : {}",
            action_list_.size(),
            actionTypeToString(action_list_.at(i).type));
    }
}

void Missi::actionHasBeenDone() {
    previous_action_has_been_done_ = true;
}

Action Missi::getCurrentAction() {
    if (hasCurrentActionTimeout()) {
        previous_action_has_been_done_ = true;
    }

    if (previous_action_has_been_done_ == true && !action_list_.empty()) {
        if (action_list_.size() <= next_action_indice_) {
            // no more action
            current_action_.type = WAIT;
            current_action_.arguments = "mission done";
            current_action_.timeout_s = 0;
        } else {
            current_action_ = action_list_.at(next_action_indice_);
            timestamp_current_action_started_ = std::chrono::system_clock::now();
            next_action_indice_++;
        }
        previous_action_has_been_done_ = false;
    }
    return current_action_;
}

bool Missi::hasCurrentActionTimeout() {
    if (current_action_.timeout_s > 0 &&
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - timestamp_current_action_started_)
                .count() > current_action_.timeout_s * 1000) {
        SPDLOG_LOGGER_INFO(logger_, "WARNING action has time outted");
        return true;
    }
    return false;
}

ActionType Missi::stringToActionType(std::string action_type_as_string) {
    if (!action_type_as_string.compare("wait")) return WAIT;
    if (!action_type_as_string.compare("grabber")) return GRABBER;
    if (!action_type_as_string.compare("move")) return MOVE;
    if (!action_type_as_string.compare("turn")) return TURN;
    if (!action_type_as_string.compare("move_backward")) return MOVE_BACKWARD;
    if (!action_type_as_string.compare("move_forward")) return MOVE_FORWARD;
    return UNKNOWN;
}

std::string Missi::actionTypeToString(ActionType action_type) {
    if (action_type == WAIT) return "wait";
    if (action_type == GRABBER) return "grabber";
    if (action_type == MOVE) return "move";
    if (action_type == TURN) return "turn";
    if (action_type == MOVE_BACKWARD) return "move_backward";
    if (action_type == MOVE_FORWARD) return "move_forward";
    if (action_type == UNKNOWN) return "unknown";
    return "unknown";
}
