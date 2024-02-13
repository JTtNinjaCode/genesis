#pragma once
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>

#include "core/core.h"
namespace Genesis {

class DLL_API Log {
 public:
  static void Init();

  static std::shared_ptr<spdlog::logger> GetCoreLogger() { return core_logger; }
  static std::shared_ptr<spdlog::logger> GetClientLogger() {
    return client_logger;
  }

 private:
  static std::shared_ptr<spdlog::logger> core_logger;
  static std::shared_ptr<spdlog::logger> client_logger;
};

}  // namespace Genesis

// assert
#ifdef ASSERT
#define CORE_ASSERT
#else
#define CORE_ASSERT
#endif

// Core log macros
#define CORE_LOG_TRACE(...) Genesis::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...) Genesis::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...) Genesis::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...) Genesis::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...) \
  Genesis::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LOG_TRACE(...) Genesis::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) Genesis::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Genesis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Genesis::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) \
  Genesis::Log::GetClientLogger()->critical(__VA_ARGS__)