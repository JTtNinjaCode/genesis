#pragma once
#include "core/core.h"
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/layer/layer.h"
#include "core/window.h"
namespace genesis {
class DLL_API ImGuiLayer : public Layer {
 public:
  static void Init(Window& window);
  static void Uninit();
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(TimeStep time_step) override;
  EventState OnEvent(Event& event) override;
  void OnRender() override;
  virtual void OnImguiRender();
};
}  // namespace genesis