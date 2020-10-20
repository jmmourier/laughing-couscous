#ifndef HAL_SIMU_H
#define HAL_SIMU_H

#include <chrono>

#include "Hali.h"

class HalSimu : public Hali {
   public:
    HalSimu();

    void updater();

    int getMd25Revision();
    int getBatteryVoltage();
    int getEncoder(MotorIdEnum id_motor);

    void setMd25Speed(int speed_1, int speed_2);

   private:
    void updateEncoder();

    int saved_speed_1_ = 127;
    int saved_speed_2_ = 127;

    std::chrono::_V2::system_clock::time_point timestamp_since_last_encoder_1_update_;
    std::chrono::_V2::system_clock::time_point timestamp_since_last_encoder_2_update_;

    int encoder_1_ = 0;
    int encoder_2_ = 0;

    const float ratio_speed_time_ = 0.001;
};

#endif  // HAL_SIMU_H