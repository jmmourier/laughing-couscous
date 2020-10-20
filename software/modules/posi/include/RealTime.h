#ifndef REALTIME_H
#define REALTIME_H

#include "IBaseTime.h"

class RealTime : public IBaseTime {
   public:
    long getDeltaTimeMS(std::chrono::duration<long, std::nano> duration) const override;
    std::chrono::_V2::system_clock::time_point getNow() const override;
};

#endif  // REALTIME_H
