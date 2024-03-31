#pragma once
#include "core/core.h"
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/layer.h"
namespace genesis {
class DLL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(TimeStep time_step) override;
  void OnEvent(Event& event) override;
  void OnRender() override;
  virtual void OnImguiRender();
};
}  // namespace genesis