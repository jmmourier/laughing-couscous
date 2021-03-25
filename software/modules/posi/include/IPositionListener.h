#ifndef IPOSITIONLISTENER_H
#define IPOSITIONLISTENER_H

#include "PositionOrientation.h"
class IPositionListener {
   public:
    virtual void onPositionChanged(const PositionOrientation &position_orientation) = 0;
};

#endif  // IPOSITIONLISTENER_H
