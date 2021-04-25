#include "Switches.h"

Switches::Switches(int pin_1, int pin_2) {
    value_switch_1_ = 0;
    value_switch_2_ = 0;
    pin_1_ = pin_1;
    pinMode(pin_1_, INPUT);
    pin_2_ = pin_2;
    pinMode(pin_2_, INPUT);
}

void Switches::updateSwitches(){
    value_switch_1_ = digitalRead(pin_1_);
    value_switch_2_ = digitalRead(pin_2_);
}

int Switches::getSwitch(SwitchId id) {
    switch(id)
    {
    case switch_id_1:
        return value_switch_1_;
        break;
    case switch_id_2:
        return value_switch_2_;
        break;
    
    default:
        return 0;
        break;
    }
}

