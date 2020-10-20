#include <iostream>
#include <string>

#include "Moti.h"

int main(int argc, char const *argv[]) {
    if (argc < 4) {
        std::cout << "Not enough arguments, Please provide Vx, Vy and omega" << std::endl;
        return 1;
    }

    Moti moti;

    float vx = stof(std::string(argv[1]));
    float vy = stof(std::string(argv[2]));
    float omega = stof(std::string(argv[3]));

    MotorSpeed motor_speed = moti.getMotorSpeedFromBaseSpeed(BaseSpeed(vx, vy, omega));

    std::cout << "accoring to input speed, motor1 = [" << motor_speed.speed_motor_1_
              << "] motor2 : [" << motor_speed.speed_motor_2_ << "]." << std::endl;

    return 0;
}
