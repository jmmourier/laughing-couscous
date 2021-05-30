#ifndef IHALILISTENER_H
#define IHALILISTENER_H

class IHaliListener {
   public:
    enum GrabberState { grabberUndefined = 0, grabberOpen = 1, grabberClose = 2 };
    enum RobotColor { YELLOW, BLUE };
    virtual void onGrabberStateChanged(const GrabberState &graberState) = 0;
};

#endif  // IHALILISTENER_H
