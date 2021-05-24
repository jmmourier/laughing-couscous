#ifndef HALI_H
#define HALI_H

#include <memory>

#include "IHaliListener.h"

enum MotorIdEnum { motor1, motor2 };
enum SwitchId { switch1, switch2 };

class IHali {
   public:
    virtual void updater() = 0;

    virtual int getMd25Revision() = 0;
    virtual int getBatteryVoltage() = 0;
    virtual int getEncoder(MotorIdEnum id_motor) = 0;

    virtual void setMd25Speed(int speed_1, int speed_2) = 0;

    virtual void setGrabber(IHaliListener::GrabberState grabber_state) = 0;
    virtual IHaliListener::GrabberState getGrabber() = 0;

    virtual bool getSwitch(SwitchId switch_id) = 0;

    virtual bool isRobotStarted() = 0;

    virtual int getDistanceObstacleCm() = 0;

    virtual void registerHaliListener(const std::weak_ptr<IHaliListener> &hali_listener) = 0;

   private:
};

#endif  // HALI_H
