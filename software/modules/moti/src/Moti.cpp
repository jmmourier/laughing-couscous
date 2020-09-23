#include "Moti.h"

Moti::Moti(){}

MotorSpeed Moti::getMotorSpeedFromBaseSpeed(BaseSpeed base_speed){
    //TODO
}

void Moti::setWheelDiameter(float wheel_diameter_mm){
    wheel_diameter_mm_ = wheel_diameter_mm;
}

void Moti::setWheelDistance(float wheel_distance_mm){
    wheel_distance_mm_ = wheel_distance_mm;
}

void Moti::setMaxWheelSpeed(float max_wheel_speed_radps){
    max_wheel_speed_radps_ = max_wheel_speed_radps;
}