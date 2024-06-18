#pragma once
#include "log.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace genesis {

void Log::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  core_logger = spdlog::stdout_color_mt("Genesis");
  core_logger->set_level(spdlog::level::trace);

  client_logger = spdlog::stdout_color_mt("app");
  client_logger->set_level(spdlog::level::trace);
}

void Log::Uninit() {}

std::shared_ptr<spdlog::logger> Log::core_logger;
std::shared_ptr<spdlog::logger> Log::client_logger;
};  // namespace genesis
