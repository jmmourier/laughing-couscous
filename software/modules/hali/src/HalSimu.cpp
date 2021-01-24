#include "HalSimu.h"

#include <iostream>
#include <string>

HalSimu::HalSimu() {
    grabber_state_ = grabberUndefined;
    timestamp_since_last_encoder_1_update_ = std::chrono::system_clock::now();
    timestamp_since_last_encoder_2_update_ = std::chrono::system_clock::now();
}

void HalSimu::updater() {
    // empty
}

int HalSimu::getMd25Revision() {
    return 1;
}

int HalSimu::getBatteryVoltage() {
    return 120;
}

int HalSimu::getEncoder(MotorIdEnum id_motor) {
    updateEncoder();
    if (id_motor == motor1) {
        return encoder_1_;
    } else {
        return encoder_2_;
    }
}

void HalSimu::setMd25Speed(int speed_1, int speed_2) {
    updateEncoder();
    saved_speed_1_ = speed_1;
    saved_speed_2_ = speed_2;
}

void HalSimu::updateEncoder() {
    auto time_update = std::chrono::system_clock::now();

    encoder_1_ = encoder_1_ + (saved_speed_1_ - 127) * ratio_speed_time_ *
                                  std::chrono::duration_cast<std::chrono::milliseconds>(
                                      time_update - timestamp_since_last_encoder_1_update_)
                                      .count();
    encoder_2_ = encoder_2_ + (saved_speed_2_ - 127) * ratio_speed_time_ *
                                  std::chrono::duration_cast<std::chrono::milliseconds>(
                                      time_update - timestamp_since_last_encoder_2_update_)
                                      .count();

    timestamp_since_last_encoder_1_update_ = time_update;
    timestamp_since_last_encoder_2_update_ = time_update;
}

void HalSimu::setGrabber(GrabberState grabber_state) {
    grabber_state_ = grabber_state;
}

GrabberState HalSimu::getGrabber() {
    return grabber_state_;
}