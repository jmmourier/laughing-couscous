#ifndef HALI_REAL_H
#define HALI_REAL_H

#include "CommandInterpreter.h"
#include "Hali.h"
#include "MessageParser.h"
#include "Serial.h"

class HalReal : public Hali {
   public:
    HalReal();

    void updater();

    int getMd25Revision();
    int getBatteryVoltage();
    int getEncoder(MotorIdEnum id_motor);

    void setMd25Speed(int speed_1, int speed_2);

   private:
    Serial serial_;
    MessageParser message_parser_;
    CommandInterpreter command_interpreter_;

    int md25_revision_ = 0;
    int md25_voltage_ = 0;
    int md25_encoder_1_ = 0;
    int md25_encoder_2_ = 0;
};

#endif  // HALI_REAL_H