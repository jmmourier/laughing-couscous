#ifndef SRF02_H
#define SRF02_H

#include <Wire.h>
#include "Arduino.h"

class Srf02{
public :
    Srf02();

    void init();
    
    // this method shall be called all the time, it handle by itself the continuous reading
    // delay between request and reply is 70ms, 
    void updateSensor();

    int getDistance();

private:
    void requestDistance();
    void readDistance();
    
    int distance_cm_;
    bool is_measurment_ready_;
    bool is_measurment_requested_;
    unsigned long last_distance_requested_time_;

};

#endif //SRF02_H