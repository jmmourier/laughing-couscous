#ifndef HALI_REAL_H
#define HALI_REAL_H

#include "CommandInterpreter.h"
#include "IHali.h"
#include "MessageParser.h"
#include "Serial.h"

class HalReal : public IHali {
   public:
    HalReal();

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
    Serial serial_;
    MessageParser message_parser_;
    CommandInterpreter command_interpreter_;

    int md25_revision_ = 0;
    int md25_voltage_ = 0;
    int md25_encoder_1_ = 0;
    int md25_encoder_2_ = 0;
    GrabberState grabber_state_;
    std::vector<std::weak_ptr<IHaliSpeedListener>> speed_listeners_;
};

#endif  // HALI_REAL_H