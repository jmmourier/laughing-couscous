#include "HalReal.h"

#include <iostream>
#include <string>

HalReal::HalReal()
    : serial_("/dev/ttyACM0", 9600),
      message_parser_(),
      command_interpreter_(),
      grabber_state_(grabberUndefined) {}

void HalReal::registerSpeedListener(const std::weak_ptr<IHaliSpeedListener> &speed_listener) {
    speed_listeners_.push_back(speed_listener);
}

void HalReal::publishToListeners() const {
    for (auto const &speed_listener_ptr : speed_listeners_) {
        if (auto speed_listener = speed_listener_ptr.lock()) {
            speed_listener->onSpeedChanged(md25_encoder_1_, md25_encoder_2_);
        }
    }
}

constexpr unsigned int hash(const char *str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h + 1) * 33) ^ str[h];
}

void HalReal::updater() {
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
                    grabber_state_ = (GrabberState)argument_received;
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
    serial_.writeString(
        message_parser_.createMessage(CommandData("md25speed1", std::to_string(speed_1))));
    serial_.writeString(
        message_parser_.createMessage(CommandData("md25speed2", std::to_string(speed_2))));
}

void HalReal::setGrabber(GrabberState grabber_state) {
    serial_.writeString(message_parser_.createMessage(
        CommandData("grabber", std::to_string(static_cast<int>(grabber_state)))));
}