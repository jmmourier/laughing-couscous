#ifndef IHALISPEEDLISTENER_H
#define IHALISPEEDLISTENER_H

class IHaliSpeedListener {
   public:
    virtual void onSpeedChanged(const int &motor1, const int &motor2) = 0;
};

#endif  // IHALISPEEDLISTENER_H
