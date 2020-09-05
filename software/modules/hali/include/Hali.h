#ifndef HALI_H
#define HALI_H

#include "MessageParser.h"
#include "Serial.h"
#include "CommandInterpreter.h"

class Hali{
public :    
    Hali();

    void updater();
    
    int getMd25Revision();
    int getBatteryVoltage();

    void setMd25Speed(int speed1, int speed2);


private : 

    void sendFirmware();

    Serial serial_;
    MessageParser message_parser_;
    CommandInterpreter command_interpreter_;    
    
    int md25Revision_ = 0;
    int md25Voltage_ = 0; 
};

#endif // HALI_H