#ifndef BASETIME_H
#define BASETIME_H

#include <chrono>

class IBaseTime {
public:
  virtual std::chrono::_V2::system_clock::time_point getNow() const = 0;
  virtual long
  getDeltaTimeMS(std::chrono::duration<long, std::nano> duration) const = 0;
};

#endif // BASETIME_H
