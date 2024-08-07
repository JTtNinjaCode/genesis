#pragma once
#include <easy/profiler.h>

#include "core/log/log.h"

#define PROFILER_FUNCTION() EASY_FUNCTION(profiler::colors::Magenta);
#define PROFILER_BLOCK(function_name) EASY_BLOCK(function_name);
#define PROFILER_END_BLOCK() EASY_END_BLOCK;

namespace genesis {
class Profiler {
 public:
  static void Init();
  static void Uninit();
};
}  // namespace genesis
