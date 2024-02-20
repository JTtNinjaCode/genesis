#pragma once
#include <functional>
#include <ostream>
#include <string>

#include "core/core.h"
#include "core/log.h"

namespace Genesis {
// EventType can be used to compare whether events are of the same type
enum class EventType {
  kNone,

  kWindowClose,
  kWindowResize,
  kWindowFocus,
  kWindowLostFocus,
  kWindowMoved,

  kApplicationTick,
  kApplicationUpdate,
  kApplicationRender,

  kKeyPressed,
  kKeyReleased,
  kKeyTyped,

  kMouseButtonPressed,
  kMouseButtonReleased,

  kMouseMoved,
  kMouseScrolled
};

enum EventCategory {
  kNoneEventCategory = 0,
  kKeyEventCategory = 1 << 0,
  kMouseEventCategory = 1 << 1,
  kMouseButtonCategory = 1 << 2,
  kApplicationEventCategory = 1 << 3,
  kWindowEventCategory = 1 << 4,
  kInputEventCategory = 1 << 5
};

#define EVENT_CLASS_TYPE(type)                                        \
  static EventType GetStaticEventType() { return EventType::##type; } \
  virtual EventType GetEventType() const override {                   \
    return GetStaticEventType();                                      \
  }                                                                   \
  virtual const char* GetEventTypeString() const override { return #type; }

// return int, because the enum EventCategory after do some or operating (ex. or
// operation)that cant convert to EventCategory
#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetEventCategoryFlags() const override { return category; }

/* this classes are used to encapulate event to dispatch other application */
class DLL_API Event {
  friend class EventDispatcher;

 public:
  virtual EventType GetEventType() const = 0;
  virtual int GetEventCategoryFlags() const = 0;
  virtual std::string ToString() const = 0;
  // TODO: GetEventName method should only use in debug
  virtual const char* GetEventTypeString() const = 0;

  inline bool IsInCategory(EventCategory event_category) {
    return (EventCategory::kNoneEventCategory ==
            (event_category & GetEventCategoryFlags()));
  }
  bool isEventHandled() const { return handled_; }

 protected:
  bool handled_ = false;
};

// EventDispatcher used to distribute event and call corresponding function to
// handle the events, It provide a method to Dispath, which is call the
// corresponding processing function according to event type and pass the event
// as a parameter to the function
class DLL_API EventDispatcher {
 public:
  template <typename T>
  using EventFunction = std::function<bool(T&)>;

  EventDispatcher(Event& event) : event_(event) {}

  template <typename T>
  bool Dispatch(EventFunction<T> event_handler) {
    if (event_.GetEventType() == T::GetStaticEventType()) {
      event_.handled_ = event_handler(static_cast<T&>(event_));
      return true;  // success to dispatch
    }
    return false;  // failed to dispatch
  }

 private:
  Event& event_;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e) {
  return os << e.ToString();
}

}  // namespace Genesis