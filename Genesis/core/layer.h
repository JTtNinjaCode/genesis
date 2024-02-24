#pragma once
#include <string>

#include "core/core.h"
#include "events/event.h"

namespace genesis {
class DLL_API Layer {
 public:
  Layer(const std::string& layer_name);
  virtual ~Layer();
  virtual void OnAttach() = 0;
  virtual void OnDetach() = 0;
  virtual void OnUpdate() = 0;
  virtual void OnEvent(Event& event) = 0;

  const std::string& GetName() const { return layer_name_; }

 private:
  std::string layer_name_;
};
}  // namespace genesis
