#ifndef HAL_SIMU_H
#define HAL_SIMU_H

#include <spdlog/logger.h>

#include <chrono>
#include <vector>

#include "IHali.h"

class HalSimu : public IHali {
   public:
    HalSimu();

    void updater() override;

    void publishToListeners() const;

    int getMd25Revision() override;
    int getBatteryVoltage() override;
    int getEncoder(MotorIdEnum id_motor) override;

    void setMd25Speed(int speed_1, int speed_2) override;

    void setGrabber(IHaliListener::GrabberState grabber_state) override;
    IHaliListener::GrabberState getGrabber() override;

    bool getSwitch(SwitchId switch_id) override;
    // this method is to artificially set the values, only in simulation
    void setSwitch(SwitchId switch_id, bool value);

    bool isRobotStarted() override;

    virtual int getDistanceObstacleCm() override;
    // this method is to artificially set the values, only in simulation
    void SetDistanceObstacleCm(int distance);

    void registerHaliListener(const std::weak_ptr<IHaliListener> &hali_listener) override;

   private:
    const int INTERVAL_ENCODERS_REFRESH_MS = 50;
    std::shared_ptr<spdlog::logger> logger_;
    void updateEncoder();

    IHaliListener::GrabberState grabber_state_;

    int saved_speed_1_ = 128;
    int saved_speed_2_ = 128;

    std::chrono::_V2::system_clock::time_point timestamp_since_last_encoder_1_update_;
    std::chrono::_V2::system_clock::time_point timestamp_since_last_encoder_2_update_;

    int encoder_1_ = 0;
    int encoder_2_ = 0;

    // 1/127 (range of speed) * 170 (tr/min max) * 360 (ticks per revolution) *
    // 1/60 (for seconds) * 1/1000 (for milliseconds)
    const float ratio_speed_time_ = 0.00803;

    bool switch_1_ = false;
    bool switch_2_ = false;

    std::chrono::_V2::system_clock::time_point timestamp_since_start_;
    bool is_robot_started_ = false;

    int distance_obstacle_cm_ = 0;
    std::vector<std::weak_ptr<IHaliListener>> hali_listeners_;
};

#endif  // HAL_SIMU_H