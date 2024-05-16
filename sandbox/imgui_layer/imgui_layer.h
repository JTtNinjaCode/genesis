#pragma once
#include <genesis.h>
namespace genesis {
class ImGuiLayer : public Layer {
 public:
  static void Init();
  static void Uninit();
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(TimeStep time_step) override;
  void OnRender() override;
  EventState OnEvent(Event& event) override;
  virtual void OnImguiRender() = 0;
};
}  // namespace genesis