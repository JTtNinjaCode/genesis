#pragma once

#include <sstream>

#include "core/events/event.h"

namespace genesis {

class MouseEvent : public Event {
  EVENT_CLASS_CATEGORY(kMouseEventCategory | kInputEventCategory)
};

class DLL_API MouseMovedEvent : public MouseEvent {
 public:
  MouseMovedEvent(double x, double y) : mouse_x_(x), mouse_y_(y) {}

  inline double GetX() const { return mouse_x_; }
  inline double GetY() const { return mouse_y_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << mouse_x_ << ", " << mouse_y_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseMoved)
 private:
  double mouse_x_, mouse_y_;
};

class DLL_API MouseScrolledEvent : public MouseEvent {
 public:
  MouseScrolledEvent(double offset_x, double offset_y)
      : offset_x_(offset_x), offset_y_(offset_y) {}

  inline double GetXOffset() const { return offset_x_; }
  inline double GetYOffset() const { return offset_y_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << GetXOffset() << ", " << GetYOffset();
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseScrolled)
 private:
  double offset_x_;
  double offset_y_;
};

class DLL_API MouseButtonEvent : public MouseEvent {
 public:
  inline int GetMouseButton() const { return button_; }

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

}  // namespace genesis