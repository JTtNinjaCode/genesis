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
  virtual void OnAttach() = 0;
  virtual void OnDetach() = 0;
  virtual void OnUpdate(TimeStep time_step) = 0;
  virtual EventState OnEvent(Event& event) = 0;
  virtual void OnRender() = 0;

  const std::string& GetName() const { return layer_name_; }

 private:
  const std::string layer_name_;
};
}  // namespace genesis
