#ifndef IWEBSERVERREQUESTLISTENER_H
#define IWEBSERVERREQUESTLISTENER_H

#include "PositionOrientation.h"
class IWebServerRequestListener {
   public:
    virtual void onWebServerPositionRequest(const PositionOrientation &position_orientation) = 0;
    virtual void onWebServerSpeedRequest(const int &motor1, const int &motor2) = 0;
    virtual void onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) = 0;
    virtual void onWebServerTargetOrientationRequest(const float &orientation_rad) = 0;
};

#endif  // IWEBSERVERREQUESTLISTENER_H
