#ifndef IPOSITIONLISTENER_H
#define IPOSITIONLISTENER_H

class IPositionListener {
   public:
    virtual void
    onPositionChanged(const double &pos_x, const double &pos_y, const double &orientation) = 0;
};

#endif  // IPOSITIONLISTENER_H
