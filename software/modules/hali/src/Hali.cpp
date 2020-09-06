#include <iostream>
#include <string>

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
            int argument_received = 0;
            if(!command_data.arguments_.empty()){
            try{
                argument_received = atoi(command_data.arguments_.at(0).c_str());
            }
            catch(...){
                return;
            }
            }
            else{
                return;
            }
            
            switch (hash(command_data.command_.c_str()))
            {
            case hash("md25revision"):
                md25Revision_ = argument_received;
                break;
            case hash("md25voltage"):
                md25Voltage_ = argument_received;
                break;
            case hash("md25encoder1"):
                md25Encoder1_ = argument_received;
                break;
            case hash("md25encoder2"):
                md25Encoder2_ = argument_received;
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

int Hali::getEncoder(MotorIdEnum id_motor){
    if(id_motor == motor1){
        return md25Encoder1_;
    }
    else {
        return md25Encoder2_;
    }
}

void Hali::setMd25Speed(int speed1, int speed2){
    serial_.writeString(message_parser_.createMessage(CommandData("md25speed1",std::to_string(speed1))));
    serial_.writeString(message_parser_.createMessage(CommandData("md25speed2",std::to_string(speed2))));
}

void Hali::sendFirmware(){

}
