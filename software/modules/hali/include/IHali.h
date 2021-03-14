#ifndef HALI_H
#define HALI_H

#include <memory>

#include "IHaliEncodersListener.h"

enum MotorIdEnum { motor1, motor2 };
enum GrabberState { grabberUndefined = 0, grabberOpen = 1, grabberClose = 2 };

class IHali {
   public:
    virtual void registerEncodersListener(
        const std::weak_ptr<IHaliEncodersListener> &encoders_listener) = 0;

    virtual void publishToListeners() const = 0;

    virtual void updater() = 0;

    virtual int getMd25Revision() = 0;
    virtual int getBatteryVoltage() = 0;
    virtual int getEncoder(MotorIdEnum id_motor) = 0;

    virtual void setMd25Speed(int speed_1, int speed_2) = 0;

    virtual void setGrabber(GrabberState grabber_state) = 0;
    GrabberState getGrabber();

   private:
};

#endif  // HALI_H
