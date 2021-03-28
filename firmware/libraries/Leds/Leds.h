#ifndef LEDS_H
#define LEDS_H

#include "Arduino.h"

enum SystemStatus { 
    waiting = 0, 
    running = 1, 
    done = 2 };

enum LedsId { 
    led_red = 0, 
    led_green = 1};

class Leds {
   public:
    Leds(int pin_led_green, int pin_led_red);

    void setStatus(SystemStatus status);
    void updateLeds();

   private:
    void toggleLed(LedsId id);

    SystemStatus status_;
    unsigned long last_change_done;
    int pin_led_green_;
    int pin_led_red_;
    bool is_green_pin_on_;
    bool is_red_pin_on_;
};

#endif  // LEDS_H