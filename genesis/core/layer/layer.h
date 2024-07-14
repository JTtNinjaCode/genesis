#pragma once
#include <string>

#include "core/core.h"
#include "core/events/event.h"
#include "core/time_step.h"

namespace genesis {
class DLL_API Layer {
 public:
  Layer(const std::string& layer_name);
  virtual ~Layer();

  virtual void OnAttach() {}
  virtual void OnDetach() {}

  virtual void OnPreUpdate() {}
  virtual void OnUpdate(TimeStep time_step) {}
  virtual void OnPostUpdate() {}

  virtual void OnRender() {}
  virtual void OnPreRender() {}
  virtual void OnPostRender() {}

  virtual EventState OnEvent(Event& event) { return EventState::kNotHandled; }

  const std::string& GetName() const { return layer_name_; }

 private:
  const std::string layer_name_;
};
}  // namespace genesis
