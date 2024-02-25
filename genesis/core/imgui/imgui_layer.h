#pragma once
#include "core/core.h"
#include "core/layer.h"
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
namespace genesis {
class DLL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate() override;
  void OnEvent(Event& event) override;

 private:
};
}  // namespace genesis