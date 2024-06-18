#include "profiler.h"
namespace genesis {
void Profiler::Init() {
  CORE_LOG_TRACE("Start to init Profiler's Context");
  EASY_PROFILER_ENABLE;
  profiler::startListen();
  CORE_LOG_TRACE("Finish to init Profiler's Context");
}

void Profiler::Uninit() {}
}  // namespace genesis