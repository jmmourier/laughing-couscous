#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include "Arduino.h"

class GameTimer{
public :
    GameTimer();

    void reset();
    void start();

    bool hasTimerReached(unsigned long time_s);

    bool isTimerCounting();

private:
    bool is_timer_counting_; 
    unsigned long time_since_started_;
};

#endif //GAME_TIMER_H