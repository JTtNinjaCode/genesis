#include "time_step.h"

namespace genesis {
TimeStep::TimeStep(float time_sec) : time_ms_(time_sec) {}

float TimeStep::GetSeconds() const { return time_ms_ * 0.001f; }

float TimeStep::GetMilliseconds() const { return time_ms_; }

}  // namespace genesis