#ifndef HAL_SIMU_H
#define HAL_SIMU_H

#include <chrono>
#include <vector>

#include "IHali.h"
#include "IHaliSpeedListener.h"

class HalSimu : public IHali {
   public:
    HalSimu();

    void registerSpeedListener(const std::weak_ptr<IHaliSpeedListener> &speed_listener) override;

    void publishToListeners() const override;

    void updater();

    int getMd25Revision();
    int getBatteryVoltage();
    int getEncoder(MotorIdEnum id_motor);

    void setMd25Speed(int speed_1, int speed_2);

    void setGrabber(GrabberState grabber_state);
    GrabberState getGrabber();

   private:
    void updateEncoder();

    GrabberState grabber_state_;

    int saved_speed_1_ = 127;
    int saved_speed_2_ = 127;

    std::chrono::_V2::system_clock::time_point timestamp_since_last_encoder_1_update_;
    std::chrono::_V2::system_clock::time_point timestamp_since_last_encoder_2_update_;

    int encoder_1_ = 0;
    int encoder_2_ = 0;

    const float ratio_speed_time_ = 0.001;

    std::vector<std::weak_ptr<IHaliSpeedListener>> speed_listeners_;
};

#endif  // HAL_SIMU_H