#ifndef INAVIREQUESTLISTENER_H
#define INAVIREQUESTLISTENER_H

class INaviRequestListener {
   public:
    virtual void onNaviSpeedRequest(const int &motor1, const int &motor2) = 0;
    virtual void onNaviTargetReachedRequest(void) = 0;
};

#endif  // INAVIREQUESTLISTENER_H
