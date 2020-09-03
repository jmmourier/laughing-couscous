#include "MessageParser.h"
#include "Serial.h"
#include "CommandInterpreter.h"

class hali{
public :    
    hali();

    void startUpdaterThread();
    void stopUpdaterThread();

    int getMd25Revision();
    int getBatteryVoltage();

    void setMd25Speed(int speed1, int speed2);


private : 
    void updater();
    void readFirmware();
    void writeFirmware();

    Serial serial_;
    MessageParser message_parser_;
    CommandInterpreter command_interpreter_;    

};
