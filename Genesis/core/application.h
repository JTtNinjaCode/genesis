#include "core.h"
#pragma once
namespace Genesis {
class DLL_API Application {
 public:
  Application(){}
  virtual void Run() = 0;
  ~Application() {}
};
};  // namespace Genesis
