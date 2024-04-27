#pragma once

#include <sstream>

#include "core/events/event.h"

namespace genesis {

class MouseEvent : public Event {
  EVENT_CLASS_CATEGORY(kMouseEventCategory | kInputEventCategory)
};

class DLL_API MouseMovedEvent : public MouseEvent {
 public:
  MouseMovedEvent(double x, double y, double delta_x, double delta_y)
      : mouse_x_(x), mouse_y_(y), mouse_delta_x_(delta_x), mouse_delta_y_(delta_y) {}

  inline double GetX() const { return mouse_x_; }
  inline double GetY() const { return mouse_y_; }
  inline double GetDeltaX() const { return mouse_delta_x_; }
  inline double GetDeltaY() const { return mouse_delta_y_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << mouse_x_ << ", " << mouse_y_;
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseMoved)
 private:
  double mouse_x_, mouse_y_;
  double mouse_delta_x_, mouse_delta_y_;
};

class DLL_API MouseScrolledEvent : public MouseEvent {
 public:
  MouseScrolledEvent(double offset_x, double offset_y) : offset_x_(offset_x), offset_y_(offset_y) {}

  inline double GetOffsetX() const { return offset_x_; }
  inline double GetOffsetY() const { return offset_y_; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << GetOffsetX() << ", " << GetOffsetY();
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseScrolled)
 private:
  double offset_x_;
  double offset_y_;
};

class DLL_API MouseButtonEvent : public MouseEvent {
 public:
  inline MouseButton GetMouseButton() const { return button_; }

 protected:
  MouseButtonEvent(MouseButton button) : button_(button) {}

  MouseButton button_;
};

class DLL_API MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  MouseButtonPressedEvent(MouseButton button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString();
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseButtonPressed)
};

class DLL_API MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  MouseButtonReleasedEvent(MouseButton button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString();
    return ss.str();
  }

  EVENT_CLASS_TYPE(kMouseButtonReleased)
};

}  // namespace genesis