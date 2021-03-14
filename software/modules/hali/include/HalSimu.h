#ifndef HAL_SIMU_H
#define HAL_SIMU_H

#include <chrono>
#include <vector>

#include "IHali.h"
#include "IHaliEncodersListener.h"

class HalSimu : public IHali {
   public:
    HalSimu();

    void registerEncodersListener(
        const std::weak_ptr<IHaliEncodersListener> &encoders_listener) override;

    void publishToListeners() const override;

    void updater() override;

    int getMd25Revision() override;
    int getBatteryVoltage() override;
    int getEncoder(MotorIdEnum id_motor) override;

    void setMd25Speed(int speed_1, int speed_2) override;

    void setGrabber(GrabberState grabber_state) override;
    GrabberState getGrabber();

   private:
    const int INTERVAL_ENCODERS_REFRESH_MS = 50;
    void updateEncoder();

    GrabberState grabber_state_;

    int saved_speed_1_ = 127;
    int saved_speed_2_ = 127;

    std::chrono::_V2::system_clock::time_point timestamp_since_last_encoder_1_update_;
    std::chrono::_V2::system_clock::time_point timestamp_since_last_encoder_2_update_;

    int encoder_1_ = 0;
    int encoder_2_ = 0;

    const float ratio_speed_time_ = 0.001;

    std::vector<std::weak_ptr<IHaliEncodersListener>> encoders_listeners_;
};

#endif  // HAL_SIMU_H