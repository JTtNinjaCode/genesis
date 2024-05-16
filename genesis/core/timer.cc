#include "timer.h"
namespace genesis {
void Timer::Start() {
  begin_time_ = std::chrono::steady_clock::now();
  last_time_ = begin_time_;
}

TimeStep Timer::GetDurationFromLastCall() {
  using namespace std::chrono;
  auto current_time = steady_clock::now();
  auto duration = current_time - last_time_;
  last_time_ = current_time;

  TimeStep time_step = duration_cast<microseconds>(duration).count() * 0.001;
  return time_step;
}

TimeStep Timer::GetDurationFromBegin() {
  using namespace std::chrono;
  auto duration = steady_clock::now() - begin_time_;

  TimeStep time_step = duration_cast<microseconds>(duration).count() * 0.001;
  return time_step;
}

}  // namespace genesis