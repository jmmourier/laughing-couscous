#include "messages_handler.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <chrono>

messages_handler::messages_handler(void) {

}

void messages_handler::handle_message(const std::string msg_str, std::string &ret){
    std::cout << "event receive "<<msg_str<<std::endl;
    if(msg_str.compare("get_bat_voltage")==0){
        ret = "bat_voltage:12.3 fake";
    } else if (msg_str.compare("get_status")==0) {
        ret = "status:ok";
    } else if (msg_str.compare("get_avr_status")==0) {
        ret = "avr_status:false";
    } else if (msg_str.compare("mvfw")==0){
        ret = "mv:f";
    } else if (msg_str.compare("mvbw")== 0){
        ret = "mv:b";
    } else if (msg_str.compare("mvl") == 0){
        ret = "mv:l";
    } else if (msg_str.compare("mvr")==0){
        ret = "mv:r";
    } else if (msg_str.compare("mvstop")==0){
        ret = "mv:stop";
    } else if (msg_str.compare("get_time")==0){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::string timehms = "time:" + std::to_string(ltm->tm_hour) +"h"+std::to_string(ltm->tm_min)+","+std::to_string(ltm->tm_sec);
        ret = timehms;
    }
    else{
        ret = "unknown command";
    }
}

