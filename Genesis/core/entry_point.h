#pragma once

#include <memory>

#include "core/application.h"
#include "core/core.h"
#include "core/log.h"

int main(int argc, char** argv) {
  genesis::Log::Init();
  CORE_LOG_WARN("Initialized Log!");

  auto app = genesis::CreateApplication();
  app->Run();
}
