#pragma once
#include "core/core.h"
#include "core/layer.h"
#include "events/mouse_event.h"
namespace Genesis {
class DLL_API ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach();
  void OnDetach();
  void OnUpdate();
  void OnEvent(Event& event);
  bool OnMousePressed(MouseButtonPressedEvent& event);
  bool OnMouseReleased(MouseButtonReleasedEvent& event);
  bool OnMouseMoved(MouseMovedEvent& event);
  bool OnMouseScrolled(MouseScrolledEvent& event); 

 private:
};
}  // namespace Genesis