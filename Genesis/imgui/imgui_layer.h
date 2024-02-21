#pragma once
#include "core/core.h"
#include "core/layer.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
namespace Genesis {
class DLL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate() override;
  void OnEvent(Event& event) override;

  bool OnMousePressed(MouseButtonPressedEvent& event);
  bool OnMouseReleased(MouseButtonReleasedEvent& event);
  bool OnMouseMoved(MouseMovedEvent& event);
  bool OnMouseScrolled(MouseScrolledEvent& event);
  bool OnKeyTyped(KeyTypedEvent& event);

 private:
};
}  // namespace Genesis