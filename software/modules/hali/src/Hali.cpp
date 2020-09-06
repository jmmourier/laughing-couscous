#include <iostream>
#include "Hali.h"

Hali::Hali():
    serial_("/dev/ttyACM0",9600),
    message_parser_(),
    command_interpreter_()
    {

}

constexpr unsigned int hash(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

void Hali::updater(){
    while(true){
        message_parser_.addCharToBuffer(serial_.readChar());
        CommandData command_data = message_parser_.analyseBuffer();
        if(!command_data.command_.empty()){
            std::cout << "data received : " << command_data << std::endl; 
            switch (hash(command_data.command_.c_str()))
            {
            case hash("md25revision"):
                md25Revision_ = atoi(command_data.arguments_.at(0).c_str());
                break;
            
            default:
                break;
            }
            //command_interpreter_.analyse(command_data);
        }
    }
}

int Hali::getMd25Revision(){
    return md25Revision_;
}

int Hali::getBatteryVoltage(){
    return md25Voltage_;
}


void Hali::setMd25Speed(int speed1, int speed2){

}

void Hali::sendFirmware(){

}
