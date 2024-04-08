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

  LoadErrorMessage();
}

const std::string& Log::GetErrorMessage(const std::string& error_message_key) {
  // TODO: insert return statement here
  return "";
}

void Log::LoadErrorMessage() {
  std::ifstream error_message_file("./assets/language/english.txt");
  auto current_path = std::filesystem::current_path();

  CORE_ASSERT(error_message_file, "Fail to open error message file.");

  while (error_message_file) {
    std::string line;
    getline(error_message_file, line);

    std::string delimiter = ":";
    size_t pos = line.find(delimiter);
    std::string key = line.substr(0, pos);
    std::string value = std::move(line.erase(0, pos + delimiter.length()));
    //error_message_map[key] = value;
  }
}

std::shared_ptr<spdlog::logger> Log::core_logger;
std::shared_ptr<spdlog::logger> Log::client_logger;
};  // namespace genesis
