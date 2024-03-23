#pragma once
#include <chrono>

#include "core/time_step.h"
namespace genesis {

class Timer {
 public:
  void Start();
  TimeStep GetDurationFromLastCall();
  TimeStep GetDurationFromBegin();

 private:
  std::chrono::steady_clock::time_point begin_time_;
  std::chrono::steady_clock::time_point last_time_;
};

}  // namespace genesis