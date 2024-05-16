#include "time_step.h"

namespace genesis {
TimeStep::TimeStep(float time_ms) : time_ms_(time_ms) {}

float TimeStep::GetSeconds() const { return time_ms_ * 0.001f; }

float TimeStep::GetMilliseconds() const { return time_ms_; }

}  // namespace genesis