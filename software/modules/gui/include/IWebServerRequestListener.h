#ifndef IWEBSERVERREQUESTLISTENER_H
#define IWEBSERVERREQUESTLISTENER_H

class IWebServerRequestListener {
   public:
    virtual void onWebServerPositionRequest(
        const double &pos_x,
        const double &pos_y,
        const double &orientation) = 0;
    virtual void onWebServerSpeedRequest(const int &motor1, const int &motor2) = 0;
    virtual void onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) = 0;
};

#endif  // IWEBSERVERREQUESTLISTENER_H
