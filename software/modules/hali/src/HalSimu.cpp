#include "HalSimu.h"

#include <iostream>
#include <string>
#include <thread>

#include "IHali.h"
#include "IHaliListener.h"
#include "logger/LoggerFactory.h"

HalSimu::HalSimu()
    : logger_(LoggerFactory::registerOrGetLogger("Hali", spdlog::level::level_enum::info)) {
    grabber_state_ = IHaliListener::GrabberState::grabberOpen;
    timestamp_since_last_encoder_1_update_ = std::chrono::system_clock::now();
    timestamp_since_last_encoder_2_update_ = std::chrono::system_clock::now();

    timestamp_since_start_ = std::chrono::system_clock::now();
}

void HalSimu::updater() {}

int HalSimu::getMd25Revision() {
    return 1;
}

int HalSimu::getBatteryVoltage() {
    return 120;
}

int HalSimu::getEncoder(MotorIdEnum id_motor) {
    updateEncoder();
    return id_motor == motor1 ? encoder_1_ : encoder_2_;
}

void HalSimu::setMd25Speed(int speed_1, int speed_2) {
    saved_speed_1_ = speed_1;
    saved_speed_2_ = speed_2;
}

void HalSimu::updateEncoder() {
    auto time_update = std::chrono::system_clock::now();

    encoder_1_ = encoder_1_ + (saved_speed_1_ - 128) * ratio_speed_time_ *
                                  std::chrono::duration_cast<std::chrono::milliseconds>(
                                      time_update - timestamp_since_last_encoder_1_update_)
                                      .count();
    encoder_2_ = encoder_2_ + (saved_speed_2_ - 128) * ratio_speed_time_ *
                                  std::chrono::duration_cast<std::chrono::milliseconds>(
                                      time_update - timestamp_since_last_encoder_2_update_)
                                      .count();

    timestamp_since_last_encoder_1_update_ = time_update;
    timestamp_since_last_encoder_2_update_ = time_update;

    SPDLOG_LOGGER_INFO(
        logger_,
        "updateEncoder encoder_1_: {} encoder_2_: {}",
        encoder_1_,
        encoder_2_);
}

void HalSimu::setGrabber(IHaliListener::GrabberState grabber_state) {
    grabber_state_ = grabber_state;
    publishToListeners();
}

IHaliListener::GrabberState HalSimu::getGrabber() {
    return grabber_state_;
}

void HalSimu::setSwitch(SwitchId switch_id, bool value) {
    switch (switch_id) {
        case switch1:
            switch_1_ = value;
            break;
        case switch2:
            switch_2_ = value;
            break;
        default:
            return;
    }
}

bool HalSimu::getSwitch(SwitchId switch_id) {
    switch (switch_id) {
        case switch1:
            return switch_1_;
        case switch2:
            return switch_2_;
        default:
            return false;
    }
}

bool HalSimu::isRobotStarted() {
    auto time_update = std::chrono::system_clock::now();
    if (is_robot_started_ == false) {
        if (std::chrono::duration_cast<std::chrono::seconds>(time_update - timestamp_since_start_)
                .count() > 3) {
            is_robot_started_ = true;
        }
    }

    return is_robot_started_;
}

int HalSimu::getDistanceObstacleCm() {
    return distance_obstacle_cm_;
}

void HalSimu::SetDistanceObstacleCm(int distance) {
    distance_obstacle_cm_ = distance;
}

void HalSimu::registerHaliListener(const std::weak_ptr<IHaliListener> &hali_listener) {
    hali_listeners_.push_back(hali_listener);
}

void HalSimu::publishToListeners() const {
    for (auto const &hali_listener_ptr : hali_listeners_) {
        if (auto hali_listener = hali_listener_ptr.lock()) {
            hali_listener->onGrabberStateChanged(grabber_state_);
        }
    }
}