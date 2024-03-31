#include "profile_timer.h"

#include "core/log.h"
namespace genesis::profile {
void ProfileTimer::Stop() {
  auto end = std::chrono::high_resolution_clock::now();
  CORE_ASSERT(running_, "Profile Timer {0} Not Running.", name_);
  running_ = false;
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start_);
  result_handler_({name_, duration});
}

ProfileTimer::~ProfileTimer() { Stop(); }
}  // namespace genesis::profile
