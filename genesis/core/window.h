#pragma once
#include <functional>
#include <string>

#include "core/core.h"
#include "events/event.h"
namespace genesis {
enum class CursorMode {
  kHidden,
  kNormal,
  kDisabled,
  kCaptured,
};
class DLL_API Window {
 public:
  using EventCallbackFunc = std::function<void(Event&)>;

  static std::shared_ptr<Window> Create(const std::string &title, unsigned int width, unsigned int height);
  virtual ~Window() = default;

  virtual void OnUpdate() = 0;

  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;

  virtual void SetCursorMode(const CursorMode cursor_mode) = 0;
  virtual void SetVSync(bool open) = 0;
  virtual bool IsVSync() const = 0;
  virtual void SetEventListener(const EventCallbackFunc& event_listener) = 0;
  virtual void* GetNativeWindow() = 0;
};
}  // namespace genesis
