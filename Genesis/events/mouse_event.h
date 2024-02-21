#pragma once

#include <sstream>

#include "event.h"

namespace Genesis {

class DLL_API MouseMovedEvent : public Event {
 public:
  MouseMovedEvent(float x, float y) : mouse_x_(x), mouse_y_(y) {}

  inline float GetX() const { return mouse_x_; }
  inline float GetY() const { return mouse_y_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << mouse_x_ << ", " << mouse_y_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseMoved)
  EVENT_CLASS_CATEGORY(kMouseEventCategory | kInputEventCategory)
 private:
  float mouse_x_, mouse_y_;
};

class DLL_API MouseScrolledEvent : public Event {
 public:
  MouseScrolledEvent(float xOffset, float yOffset)
      : offset_x_(xOffset), offset_y_(yOffset) {}

  inline float GetXOffset() const { return offset_x_; }
  inline float GetYOffset() const { return offset_y_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << GetXOffset() << ", " << GetYOffset();
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseScrolled)
  EVENT_CLASS_CATEGORY(kMouseEventCategory | kInputEventCategory)
 private:
  float offset_x_, offset_y_;
};

class DLL_API MouseButtonEvent : public Event {
 public:
  inline int GetMouseButton() const { return button_; }

  EVENT_CLASS_CATEGORY(kMouseEventCategory | kInputEventCategory)
 protected:
  MouseButtonEvent(int button) : button_(button) {}

  int button_;
};

class DLL_API MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << button_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseButtonPressed)
};

class DLL_API MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << button_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseButtonReleased)
};

}  // namespace Genesis