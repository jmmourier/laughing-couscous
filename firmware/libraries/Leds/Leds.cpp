#include "Leds.h"


Leds::Leds(int pin_led_green, int pin_led_red){
    pin_led_green_ = pin_led_green;
    pin_led_red_ = pin_led_red;
    
    pinMode(pin_led_green_, OUTPUT);
    digitalWrite(pin_led_green_,HIGH);
    is_green_pin_on_ = true;

    pinMode(pin_led_red_, OUTPUT);
    digitalWrite(pin_led_green_,LOW);
    is_red_pin_on_ = false;
    
    status_ = waiting;
}

void Leds::setStatus(SystemStatus status) {
    status_ = status;
}

void Leds::updateLeds(){
    switch (status_)
    {
    case waiting:
        if (millis()-last_change_done > 1000)
        {
            toggleLed(led_red);
            toggleLed(led_green);
            last_change_done = millis();
        }
        break;
    case running:
        if(is_red_pin_on_ == is_green_pin_on_) {
            is_red_pin_on_ =! is_red_pin_on_;
        }
        if (millis()-last_change_done > 100)
        {
            toggleLed(led_red);
            toggleLed(led_green);
            last_change_done = millis();
        }
        break;
    case done:
        digitalWrite(pin_led_red_, HIGH);
        digitalWrite(pin_led_green_, HIGH);       
        break;

    default:
        break;
    }
}

void Leds::toggleLed(LedsId id){
    switch (id)
    {
    case led_red:
        if(is_red_pin_on_) {
            is_red_pin_on_ = false;
            digitalWrite(pin_led_red_,LOW);
        }
        else {
            is_red_pin_on_ = true;
            digitalWrite(pin_led_red_,HIGH);
        }
        break;
    case led_green:
        if(is_green_pin_on_) {
            is_green_pin_on_ = false;
            digitalWrite(pin_led_green_,LOW);
        }
        else {
            is_green_pin_on_ = true;
            digitalWrite(pin_led_green_,HIGH);
        }
        break;
    
    default:
        break;
    }
}