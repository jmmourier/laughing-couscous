#ifndef IWEBSERVERLISTENER_H
#define IWEBSERVERLISTENER_H

class IWebServerListener {
   public:
    virtual void
    onPositionRequested(const double &pos_x, const double &pos_y, const double &orientation) = 0;

    virtual void onSpeedRequested(const int &motor1, const int &motor2) = 0;
};

#endif  // IWEBSERVERLISTENER_H
