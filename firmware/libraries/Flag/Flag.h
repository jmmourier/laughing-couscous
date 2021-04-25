#ifndef FLAG_H
#define FLAG_H

#include <Servo.h>

#include "Arduino.h"

enum FlagState { flagUp = 1, flagDown = 2 };

class Flag {
   public:
    Flag(int pin);

    void init();
    void setFlag(FlagState state);

   private:
    Servo servo_;
    int pin_;
};

#endif  // FLAG_H