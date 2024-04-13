#pragma once

#include <memory>

#include "core/application.h"
#include "core/core.h"
#include "core/log/log.h"

int main(int argc, char** argv) {
  auto app = genesis::CreateApplication();
  app->Run();
}
