#include "messages_handler.h"

#include <iostream>
#include <ctime>
#include "Hali.h"
#include "HalSimu.h"

messages_handler::messages_handler(Hali *hali) : _hali(hali) {}


void messages_handler::handle_message(const std::string msg_str, std::string &ret){
    //std::cout << "event receive "<<msg_str<<std::endl;
    if(msg_str.compare("get_bat_voltage")==0){
        ret = "bat_voltage:"+std::to_string(_hali->getBatteryVoltage());
    } else if (msg_str.compare("get_status")==0) {
        ret = "status:ok";
    }else if (msg_str.compare("get_encoder_1")==0) {
        ret = "encoder_1:"+std::to_string(_hali->getEncoder(motor1));
    } else if (msg_str.compare("get_ecoder_2")==0){
        ret = "encoder_2:"+std::to_string(_hali->getEncoder(motor2));
    } else if (msg_str.compare("mvfw")==0){
        _hali->setMd25Speed(10,10);
        ret = "mv:fw";
    } else if (msg_str.compare("mvbw")== 0){
        _hali->setMd25Speed(-10,-10);
        ret = "mv:bw";
    } else if (msg_str.compare("mvl") == 0){
        ret = "mv:l";
    } else if (msg_str.compare("mvr")==0){
        ret = "mv:r";
    } else if (msg_str.compare("mvstop")==0){
        _hali->setMd25Speed(0,0);
        ret = "mv:stop";
    } else if (msg_str.compare("get_time")==0){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::string timehms = "time:" + std::to_string(ltm->tm_hour) +"h "+std::to_string(ltm->tm_min)+"m "+std::to_string(ltm->tm_sec)+"s";
        ret = timehms;
    } else if (msg_str.compare("get_avr_status")==0) {
        ret = "avr_status:false";
    }else{
        ret = "messages handler: unknown command";
    }
}

