#include "RealTime.h"

long RealTime::getDeltaTimeMS(
    std::chrono::duration<long, std::nano> duration) const {
  return std::chrono::duration_cast<std::chrono::milliseconds>(duration)
      .count();
}

std::chrono::_V2::system_clock::time_point RealTime::getNow() const {
  return std::chrono::system_clock::now();
}