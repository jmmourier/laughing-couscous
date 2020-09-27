#include "FakeTime.h"

FakeTime::FakeTime(long delta_time_ms) : delta_time_ms_(delta_time_ms) {}

long FakeTime::getDeltaTimeMS(
    std::chrono::duration<long, std::nano> duration) const {
  return delta_time_ms_;
}

std::chrono::_V2::system_clock::time_point FakeTime::getNow() const {
  return std::chrono::system_clock::now();
}