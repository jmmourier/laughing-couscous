#ifndef HALI_REAL_H
#define HALI_REAL_H

#include "Hali.h"
#include "MessageParser.h"
#include "Serial.h"
#include "CommandInterpreter.h"


class HalReal : public Hali{
public :    
    HalReal();

    void updater();
    
    int getMd25Revision();
    int getBatteryVoltage();
    int getEncoder(MotorIdEnum id_motor);

    void setMd25Speed(int speed1, int speed2);


private : 

    Serial serial_;
    MessageParser message_parser_;
    CommandInterpreter command_interpreter_;    
    
    int md25Revision_ = 0;
    int md25Voltage_ = 0; 
    int md25Encoder1_ = 0;
    int md25Encoder2_ = 0;
};

#endif // HALI_REAL_H