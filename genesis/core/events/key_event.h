#pragma once
#include <sstream>
#include <string>

#include "core/core.h"
#include "core/events/event.h"
#include "core/input.h"
namespace genesis {
class DLL_API KeyEvent : public Event {
 public:
  EVENT_CLASS_CATEGORY(kKeyEventCategory | kInputEventCategory)
};

class DLL_API KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(Keycode key_code) : key_code_(key_code) {
    CORE_LOG_TRACE(ToString());
  }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString()
       << Input::GetInstance().GetKeyCodeName(key_code_);
    return ss.str();
  }

  Keycode GetKeyCode() const { return key_code_; }

  EVENT_CLASS_TYPE(kKeyPressed)
 private:
  Keycode key_code_;
};

class DLL_API KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(Keycode keycode) : key_code_(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString();
    return ss.str();
  }

  Keycode GetKeyCode() const { return key_code_; }

  EVENT_CLASS_TYPE(kKeyReleased)
 private:
  Keycode key_code_;
};

class DLL_API KeyTypedEvent : public KeyEvent {
 public:
  KeyTypedEvent(unsigned int input_character) : character_(input_character) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << ' ' << character_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kKeyTyped)
  unsigned int character_;
};
}  // namespace genesis