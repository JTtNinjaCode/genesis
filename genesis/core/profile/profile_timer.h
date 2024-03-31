#pragma once
#include <chrono>
#include <functional>
#include <string>
namespace genesis::profile {
#define PROFILE(name, result_handler) \
  genesis::profile::ProfileTimer profiler##__LINE__(name, result_handler);

struct ProfileResult {
  const char* name;
  std::chrono::microseconds duration;
};

class ProfileTimer {
 public:
  // only for constant string
  ProfileTimer(const char* name,
               std::function<void(const ProfileResult&)> result_handler)
      : name_(name),
        running_(true),
        start_(std::chrono::high_resolution_clock::now()),
        result_handler_(result_handler) {}

  void Stop();
  ~ProfileTimer();

 private:
  bool running_ = false;
  std::chrono::steady_clock::time_point start_;
  const char* name_;
  std::function<void(const ProfileResult&)> result_handler_;
};
}  // namespace genesis::profile
