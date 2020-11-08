#ifndef GRABBER_H
#define GRABBER_H

#include "Arduino.h"
#include <Servo.h> 

enum GrabberState { grabberUndefined = 0, grabberOpened = 1, grabberClosed = 2};

class Grabber{
public :
    Grabber(int pin);

    void init();
    void open();
    void close();

    int getGrabber();

private:
    Servo servo_;
    int pin_;
    GrabberState grabber_state_;
};

#endif //GRABBER_H