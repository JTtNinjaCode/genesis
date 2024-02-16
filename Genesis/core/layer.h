#pragma once
#include <string>

#include "core.h"
#include "events/event.h"

namespace Genesis {
class DLL_API Layer {
 public:
  Layer(const std::string& layer_name);
  virtual ~Layer();
  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnEvent(Event& event) {}

  const std::string& GetName() const { return layer_name_; }

 private:
  std::string layer_name_;
};
}  // namespace Genesis
