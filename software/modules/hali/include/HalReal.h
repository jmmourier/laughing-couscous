#ifndef HALI_REAL_H
#define HALI_REAL_H

#include <spdlog/logger.h>

#include "CommandInterpreter.h"
#include "IHali.h"
#include "IHaliListener.h"
#include "MessageParser.h"
#include "Serial.h"

class HalReal : public IHali {
   public:
    HalReal();

    void updater() override;

    void publishToListeners() const;

    int getMd25Revision() override;
    int getBatteryVoltage() override;
    int getEncoder(MotorIdEnum id_motor) override;

    void setMd25Speed(int speed_1, int speed_2) override;

    void setGrabber(IHaliListener::GrabberState grabber_state) override;
    IHaliListener::GrabberState getGrabber() override;

    bool getSwitch(SwitchId switch_id) override;

    bool isRobotStarted() override;

    virtual int getDistanceObstacleCm() override;

    void registerHaliListener(const std::weak_ptr<IHaliListener> &hali_listener) override;

   private:
    void resetEncoder();

    Serial serial_;
    MessageParser message_parser_;
    CommandInterpreter command_interpreter_;
    std::shared_ptr<spdlog::logger> logger_;

    int md25_revision_ = 0;
    int md25_voltage_ = 0;
    int md25_encoder_1_ = 0;
    int md25_encoder_2_ = 0;
    IHaliListener::GrabberState grabber_state_;
    bool switch_1_ = false;
    bool switch_2_ = false;
    bool is_robot_started_ = false;
    int distance_obstacle_cm_ = 0;
    std::vector<std::weak_ptr<IHaliListener>> hali_listeners_;
};

#endif  // HALI_REAL_H