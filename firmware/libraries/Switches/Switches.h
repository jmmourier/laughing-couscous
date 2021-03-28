#ifndef SWITCHES_H
#define SWITCHES_H

#include "Arduino.h"

enum SwitchId {switch_id_1 = 0, switch_id_2 = 1};

class Switches {
   public:
    Switches(int pin_1, int pin_2);

    void updateSwitches();

    int getSwitch(SwitchId id); 

   private:
    int pin_1_;
    int value_switch_1_;
    int pin_2_;
    int value_switch_2_;
};

#endif  // SWITCHES_H