#ifndef FAKETIME_H
#define FAKETIME_H

#include "IBaseTime.h"

class FakeTime : public IBaseTime {
   public:
    explicit FakeTime(long delta_time_ms_);
    long getDeltaTimeMS(std::chrono::duration<long, std::nano> duration) const override;
    std::chrono::_V2::system_clock::time_point getNow() const override;

   private:
    long delta_time_ms_;
};

#endif  // FAKETIME_H
