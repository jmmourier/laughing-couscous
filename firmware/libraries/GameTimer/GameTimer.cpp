#include "GameTimer.h"

GameTimer::GameTimer(){
    time_since_started_ = 0;
    is_timer_counting_ = false;
}

void GameTimer::start(){
    time_since_started_ = millis();
    is_timer_counting_ = true;
}

void GameTimer::reset(){
    is_timer_counting_ = false;
}

bool GameTimer::hasTimerReached(unsigned long time_ms) {
    if( is_timer_counting_ == true &&
        millis()-time_since_started_ > time_ms){
        return true;
    } else {
        return false;
    }
    
}

bool GameTimer::isTimerCounting(){
    return is_timer_counting_;
}