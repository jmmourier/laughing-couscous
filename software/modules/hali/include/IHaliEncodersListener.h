#ifndef IHALIENCODERSLISTENER_H
#define IHALIENCODERSLISTENER_H

class IHaliEncodersListener {
   public:
    virtual void onEncodersChanged(const int &encoders_motor1, const int &encoders_motor2) = 0;
};

#endif  // IHALIENCODERSLISTENER_H
