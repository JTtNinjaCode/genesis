#pragma once
#include "core/log.h"

namespace Genesis {

void Log::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  core_logger = spdlog::stdout_color_mt("Genesis");
  core_logger->set_level(spdlog::level::trace);

  client_logger = spdlog::stdout_color_mt("app");
  client_logger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> Log::core_logger;
std::shared_ptr<spdlog::logger> Log::client_logger;
};  // namespace Genesis
