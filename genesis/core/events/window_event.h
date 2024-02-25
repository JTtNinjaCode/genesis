#pragma once
#include <sstream>
#include <string>

#include "core/core.h"
#include "core/events/event.h"

namespace genesis {
class WindowCloseEvent : public Event {
 public:
  WindowCloseEvent() {}

  std::string ToString() const override { return GetEventTypeString(); }
  EVENT_CLASS_TYPE(kWindowClose)
  EVENT_CLASS_CATEGORY(kWindowEventCategory)
};

class WindowResizeEvent : public Event {
 public:
  WindowResizeEvent(int width, int height) : width_(width), height_(height) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetEventTypeString() << ' ' << width_ << ", " << height_;
    return ss.str();
  }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  EVENT_CLASS_TYPE(kWindowResize)
  EVENT_CLASS_CATEGORY(kWindowEventCategory)

 private:
  int width_;
  int height_;
};

// TODO: add WindowMoved, WindowFocus, WindowLostFocus
// class WindowFocus : public Event {
//  WindowFocus() {}
//};
// class WindowLostFocus : public Event {
//  WindowLostFocus() {}
//};
// class WindowMoved : public Event {
//  WindowMoved(){
//  }
//};
}  // namespace genesis