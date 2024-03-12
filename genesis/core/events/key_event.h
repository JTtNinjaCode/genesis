#pragma once
#include <sstream>
#include <string>

#include "core/core.h"
#include "core/events/event.h"
#include "core/input.h"
namespace genesis {
class DLL_API KeyEvent : public Event {
 public:
  KeyEvent(Keycode key_code) : key_code_(key_code) {}

  Keycode GetKeyCode() const { return key_code_; }
  EVENT_CLASS_CATEGORY(kKeyEventCategory | kInputEventCategory)

 protected:
  Keycode key_code_;
};

class DLL_API KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(Keycode key_code) : KeyEvent(key_code) {}

  std::string ToString() const override {
    std::stringstream ss;
    // ss << GetEventTypeString() << ' ' << key_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kKeyPressed)
};

class DLL_API KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(Keycode keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    // ss << GetEventTypeString() << ' ' << key_code_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kKeyReleased)
};

class DLL_API KeyTypedEvent : public KeyEvent {
 public:
  // KeyEvent in this class is useless, because this event does not have keycode
  // TODO: should sperate typeevent form keyevent
  KeyTypedEvent(unsigned int input_character)
      : KeyEvent(Keycode::kKeyUnknown), character(input_character) {}

  std::string ToString() const override {
    std::stringstream ss;
    // ss << GetEventTypeString() << ' ' << key_code_;
    return ss.str();
  }

  unsigned int character;

  EVENT_CLASS_TYPE(kKeyTyped)
};
}  // namespace genesis