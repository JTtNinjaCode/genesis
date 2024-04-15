#pragma once
#include <functional>
#include <string>

#include "core/core.h"
#include "events/event.h"
namespace genesis {
class DLL_API Window {
 public:
  using EventCallbackFunc = std::function<void(Event&)>;

  static std::shared_ptr<Window> Create(std::string title, unsigned int widht, unsigned int height);
  virtual ~Window() = default;

  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;
  virtual void EnableCursor(bool open) = 0;
  virtual void SetVSync(bool open) = 0;
  virtual bool IsVSync() const = 0;
  virtual void SetEventListener(const EventCallbackFunc& event_listener) = 0;
  virtual void* GetNativeWindow() = 0;

  virtual void OnUpdate() = 0;
};
}  // namespace genesis
