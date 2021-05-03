#include "Navi.h"

#include <spdlog/logger.h>

#include <cmath>
#include <iostream>

#include "NaviUtils.h"
#include "logger/LoggerFactory.h"

#define TARGET_REACHED_DISTANCE 0.02
#define TARGET_ANGLE_REACHED_RAD 0.02
#define MAX_ROTATION 0.35
#define ANGLE_FOR_ROTATION_ONLY_RAD 0.25
#define MAX_SPEED 0.5

Navi::Navi()
    : logger_(LoggerFactory::registerOrGetLogger("Navi", spdlog::level::level_enum::info)) {}

void Navi::registerNaviRequestListener(const std::weak_ptr<INaviRequestListener> &navi_listener) {
    navi_listeners_.push_back(navi_listener);
}

// void Navi::publishToNaviSpeedRequestListeners(const int &motor1, const int &motor2) const {
void Navi::publishToNaviSpeedRequestListeners(
    const float &v_x_mps,
    const float &v_y_mps,
    const float &omega_radps) const {
    for (auto const &navi_listener_ptr : navi_listeners_) {
        if (auto navi_listener = navi_listener_ptr.lock()) {
            navi_listener->onNaviSpeedRequest(v_x_mps, v_y_mps, omega_radps);
        }
    }
}

void Navi::publishToNaviTargetReachedListeners(void) const {
    for (auto const &navi_listener_ptr : navi_listeners_) {
        if (auto navi_listener = navi_listener_ptr.lock()) {
            navi_listener->onNaviTargetReachedRequest();
        }
    }
}

int Navi::setTargetPosition(
    const double &target_pos_x,
    const double &target_pos_y,
    const double &target_orientation) {
    std::cout << "[Navi] set target position" << target_pos_x << " " << target_pos_y << std::endl;
    target_position_.pos_x = target_pos_x;
    target_position_.pos_y = target_pos_y;
    target_position_.orientation = target_orientation;
    is_position_idle_ = false;
    return 0;
}

int Navi::setTargetOrientation(double target_orientation) {
    std::cout << "[Navi] set orientation" << target_orientation << std::endl;
    target_position_.orientation = target_orientation;

    is_orientation_idle_ = false;
    return 0;
}

int Navi::setTargetOrientation(const float &orientation_rad) {
    target_position_.orientation = orientation_rad;
}

int Navi::setCurrentPosition(
    const double &new_rob_pos_x,
    const double &new_rob_pos_y,
    const double &new_rob_orientation) {
    actual_robot_position_.pos_x = new_rob_pos_x;
    actual_robot_position_.pos_y = new_rob_pos_y;
    actual_robot_position_.orientation = new_rob_orientation;
    if (!is_position_idle_) {
        computeSpeed(actual_robot_position_, target_position_);
    }
    if (!is_orientation_idle_) {
        computeRotationSpeed(new_rob_orientation, target_position_.orientation);
    }

    // std::cout << "set current posisiton" << is_position_idle_ << std::endl;
    return 0;
}

void Navi::computeSpeed(const pos_info &robot_pos, const pos_info &target_pos) {
    // std::cout << "compute speed" << std::endl;
    double distance = getDistanceToTarget(robot_pos, target_pos);
    double rotation, speed = 0;
    // hasPositionBeenReached
    if (std::abs(distance) < TARGET_REACHED_DISTANCE) {
        rotation = 0;
        speed = 0;
        publishToNaviSpeedRequestListeners(0, 0, 0);
        publishToNaviTargetReachedListeners();
        is_position_idle_ = true;
        std::cout << "navi:: target reached" << std::endl;
        is_idle_ = true;
        return;
    }

    // cap regulation
    double errorCap = shortcut_getAngleToTarget(robot_pos, target_pos);

    if (errorCap > M_PI) {
        errorCap = errorCap - (2 * M_PI);
    }
    if (errorCap < -M_PI) {
        errorCap = errorCap + (2 * M_PI);
    }

    rotation = errorCap;
    if (rotation > MAX_ROTATION) rotation = MAX_ROTATION;
    if (rotation < -MAX_ROTATION) rotation = -MAX_ROTATION;

    // Speed regulation
    if (std::abs(errorCap) > ANGLE_FOR_ROTATION_ONLY_RAD) {
        std::cout << "Navi::error cap = " << errorCap << std::endl;
        speed = 0;
    } else {
        speed = distance;
        std::cout << "Navi::update dist :" << distance << " errorCap" << errorCap << std::endl;
        if (speed > MAX_SPEED) speed = MAX_SPEED;
    }

    publishToNaviSpeedRequestListeners(speed, 0, rotation);
}

void Navi::computeRotationSpeed(const double robot_orientation, const double target_orientation) {
    double errorCap = std::abs(robot_orientation - target_orientation);
    if (errorCap < TARGET_ANGLE_REACHED_RAD) {
        std::cout << "angle target reached" << std::endl;
        publishToNaviSpeedRequestListeners(0, 0, 0);
        publishToNaviTargetReachedListeners();
        is_orientation_idle_ = true;
        return;
    }

    rotdir rotation_direction = getRotationDir(robot_orientation, target_orientation);
    if (rotation_direction == rotdir::Clockwise) {
        publishToNaviSpeedRequestListeners(0, 0, -MAX_SPEED);
    } else {
        publishToNaviSpeedRequestListeners(0, 0, MAX_SPEED);
    }
    std::cout << "[Navi] robot_orientation: " << robot_orientation << " errorCap= " << errorCap
              << " " << rotation_direction << std::endl;
}