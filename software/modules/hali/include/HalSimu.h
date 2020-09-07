#ifndef HAL_SIMU_H
#define HAL_SIMU_H

#include <chrono>

#include "Hali.h"


class HalSimu : public Hali{
public :    
    HalSimu();

    void updater();
    
    int getMd25Revision();
    int getBatteryVoltage();
    int getEncoder(MotorIdEnum id_motor);

    void setMd25Speed(int speed_1, int speed_2);

private : 

    void updateEncoder();

    int saved_speed_1_ = 0;
    int saved_speed_2_ = 0;
    std::chrono::seconds timestamp_speed_1_;
    std::chrono::seconds timestamp_speed_2_;
    //    const auto p1 = std::chrono::system_clock::now();

    int encoder_1_ = 0;
    int encoder_2_ = 0;

};

#endif // HAL_SIMU_H