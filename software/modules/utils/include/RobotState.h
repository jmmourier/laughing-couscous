
#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include "PositionOrientation.h"
#include "Types.h"

struct RobotState {
    RobotState(
        const PositionOrientation &position_orientation,
        const float &battery,
        const bool &is_grabber_open,
        const long &mission_started_at,
        const long &mission_ended_at,
        ActionType current_action)
        : position_orientation_(position_orientation),
          battery_(battery),
          is_grabber_open_(is_grabber_open),
          mission_started_at_(mission_started_at),
          mission_ended_at_(mission_ended_at),
          current_action_(current_action) {}
    PositionOrientation position_orientation_;
    float battery_;
    bool is_grabber_open_;
    long mission_started_at_;
    long mission_ended_at_;
    ActionType current_action_;
};

#endif  // ROBOT_STATE_H