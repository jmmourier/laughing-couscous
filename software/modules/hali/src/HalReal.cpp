#include "HalReal.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "logger/LoggerFactory.h"

HalReal::HalReal()
    : logger_(LoggerFactory::registerOrGetLogger("Hali", spdlog::level::level_enum::info)),
      serial_("/dev/ttyACM0", 9600),
      message_parser_(),
      command_interpreter_(),
      grabber_state_(IHaliListener::GrabberState::grabberOpen) {
    resetEncoder();
    std::cout << "[hali] request reset encoder" << std::endl;
    std::this_thread::sleep_for(std::chrono::duration<float, std::ratio<1, 1000>>(100));
    std::cout << "[hali] reset encoder considered done" << std::endl;
    serial_.flushReceiver();
}

constexpr unsigned int hash(const char *str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h + 1) * 33) ^ str[h];
}

void HalReal::updater() {
    serial_.flushReceiver();  // just to be sure
    while (true) {
        message_parser_.addCharToBuffer(serial_.readChar());
        CommandData command_data = message_parser_.analyseBuffer();
        if (!command_data.command_.empty()) {
            std::cout << "data received : " << command_data << std::endl;
            int argument_received = 0;
            if (!command_data.arguments_.empty()) {
                try {
                    argument_received = atoi(command_data.arguments_.at(0).c_str());
                } catch (...) {
                    return;
                }
            } else {
                return;
            }

            switch (hash(command_data.command_.c_str())) {
                case hash("md25revision"):
                    md25_revision_ = argument_received;
                    break;
                case hash("md25voltage"):
                    md25_voltage_ = argument_received;
                    break;
                case hash("md25encoder1"):
                    md25_encoder_1_ = argument_received;
                    break;
                case hash("md25encoder2"):
                    md25_encoder_2_ = argument_received;
                    break;
                case hash("grabberState"):
                    grabber_state_ = (IHaliListener::GrabberState)argument_received;
                    break;
                case hash("robotStarted"):
                    if (argument_received == 0) {
                        is_robot_started_ = false;
                    } else {
                        is_robot_started_ = true;
                    }
                    break;
                case hash("switch1"):
                    if (argument_received == 0) {
                        switch_1_ = false;
                    } else {
                        switch_1_ = true;
                    }
                    break;
                case hash("switch2"):
                    if (argument_received == 0) {
                        switch_2_ = false;
                    } else {
                        switch_2_ = true;
                    }
                    break;
                case hash("distance"):
                    distance_obstacle_cm_ = argument_received;
                    break;
                default:
                    break;
            }
        }
    }
}

int HalReal::getMd25Revision() {
    return md25_revision_;
}

int HalReal::getBatteryVoltage() {
    return md25_voltage_;
}

int HalReal::getEncoder(MotorIdEnum id_motor) {
    if (id_motor == motor1) {
        return md25_encoder_1_;
    } else {
        return md25_encoder_2_;
    }
}

void HalReal::setMd25Speed(int speed_1, int speed_2) {
    SPDLOG_LOGGER_INFO(logger_, "setMd25Speed speed1: {} speed2: {}", speed_1, speed_2);
    serial_.writeString(
        message_parser_.createMessage(CommandData("md25speed1", std::to_string(speed_1))));
    serial_.writeString(
        message_parser_.createMessage(CommandData("md25speed2", std::to_string(speed_2))));
}

void HalReal::setGrabber(IHaliListener::GrabberState grabber_state) {
    serial_.writeString(message_parser_.createMessage(
        CommandData("grabber", std::to_string(static_cast<int>(grabber_state)))));
    grabber_state_ = grabber_state;
    publishToListeners();
}

IHaliListener::GrabberState HalReal::getGrabber() {
    return grabber_state_;
}

bool HalReal::getSwitch(SwitchId switch_id) {
    switch (switch_id) {
        case switch1:
            return switch_1_;
        case switch2:
            return switch_2_;
        default:
            return false;
    }
}

bool HalReal::isRobotStarted() {
    return is_robot_started_;
}

int HalReal::getDistanceObstacleCm() {
    return distance_obstacle_cm_;
}

void HalReal::resetEncoder() {
    serial_.writeString(message_parser_.createMessage(CommandData("resetEncoder", "0")));
    return;
}

void HalReal::registerHaliListener(const std::weak_ptr<IHaliListener> &hali_listener) {
    hali_listeners_.push_back(hali_listener);
}

void HalReal::publishToListeners() const {
    for (auto const &hali_listener_ptr : hali_listeners_) {
        if (auto hali_listener = hali_listener_ptr.lock()) {
            hali_listener->onGrabberStateChanged(grabber_state_);
        }
    }
}