#include "Flag.h"

Flag::Flag(int pin) {
    pin_ = pin;
}

void Flag::init() {
    servo_.attach(pin_);
}

void Flag::setFlag(FlagState state) {
    if (state == flagUp) {
        servo_.write(0);
    } else {  // flagDown
        servo_.write(100);
	}
}
