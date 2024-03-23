#pragma once
namespace genesis {
class TimeStep {
 public:
  TimeStep(float time_ms = 0.0f);
  float GetSeconds() const;
  float GetMilliseconds() const;

 private:
  float time_ms_ = 0.0f;
};

}  // namespace genesis