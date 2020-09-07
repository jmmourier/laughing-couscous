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

void HalSimu::setMd25Speed(int speed1, int speed2){
    // todo
}
