#include <iostream>
#include <string>

#include "HalSimu.h"

HalSimu::HalSimu(){

}

void HalSimu::updater(){
    // empty
}

int HalSimu::getMd25Revision(){
    return 1;
}

int HalSimu::getBatteryVoltage(){
    std::cout << "child called" << std::endl;
    return 120;
}

int HalSimu::getEncoder(MotorIdEnum id_motor){
    // todo
    return 0;
}

void HalSimu::setMd25Speed(int speed_1, int speed_2){
    updateEncoder(); 
    saved_speed_1_ = speed_1;
    saved_speed_2_ = speed_2;
}

void HalSimu::updateEncoder(){

}