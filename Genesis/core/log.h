#pragma once
#pragma warning(push)
#pragma warning(disable : 4819)
#pragma warning(disable : 26498)
#pragma warning(disable : 26800)
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#pragma warning(pop)

#include <memory>

#include "core/core.h"
namespace genesis {

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
}  // namespace genesis

// Core log macros
#define CORE_LOG_TRACE(...) genesis::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...) genesis::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...) genesis::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...) genesis::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...) \
  genesis::Log::GetCoreLogger()->critical(__VA_ARGS__)

// assert
#ifdef ASSERT
#define CORE_ASSERT(x, msg) \
  if (!(x)) {               \
    CORE_LOG_ERROR(msg);    \
    __debugbreak();         \
  }
#else
#define CORE_ASSERT(x, msg)
#endif

// Client log macros
#define LOG_TRACE(...) genesis::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) genesis::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) genesis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) genesis::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) genesis::Log::GetClientLogger()->critical(__VA_ARGS__)