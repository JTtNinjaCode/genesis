#pragma once
#include <sstream>
#include <string>

#include "core/core.h"
#include "event.h"
namespace Genesis {
class DLL_API KeyEvent : public Event {
 public:
  KeyEvent(int key_code) : key_code_(key_code) {}

  int GetKeyCode() const { return key_code_; }
  EVENT_CLASS_CATEGORY(kKeyEventCategory | kInputEventCategory)

 protected:
  int key_code_;
};

class DLL_API KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(int key_code) : KeyEvent(key_code) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << ' ' << key_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kKeyPressed)
};

class DLL_API KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << ' ' << key_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kKeyReleased)
};

class DLL_API KeyTypedEvent : public KeyEvent {
 public:
  KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << ' ' << key_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kKeyTyped)
};
}  // namespace Genesis