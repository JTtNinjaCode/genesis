#pragma once

#include <memory>

#include "application.h"
#include "core/core.h"
#include "log.h"

int main(int argc, char** argv) {
  genesis::Log::Init();
  CORE_LOG_WARN("Initialized Log!");

  auto app = genesis::CreateApplication();
  app->Run();
}
