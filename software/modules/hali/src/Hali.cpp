#include "Hali.h"

Hali::Hali():
    serial_("/dev/ttyACM0",9600),
    message_parser_(),
    command_interpreter_()
    {

}

void Hali::updater(){
    while(true){
        message_parser_.addCharToBuffer(serial_.readChar());
        CommandData command_data = message_parser_.analyseBuffer();
        if(!command_data.command_.empty()){
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
