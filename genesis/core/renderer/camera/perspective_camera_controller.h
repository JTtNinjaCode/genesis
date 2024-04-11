#pragma once
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/events/window_event.h"
#include "core/renderer/camera/orthographic_camera.h"
#include "core/renderer/camera/perspective_camera.h"
#include "core/time_step.h"
namespace genesis {
class PerspectiveCameraController {
 public:
  PerspectiveCameraController(float height, float ratio, float near_plane,
                               float far_plane);
  bool OnEvent(Event& event) {
    EventDispatcher event_dispatcher(event);
    event_dispatcher.Dispatch<WindowResizeEvent>(
        BIND_METHOD(PerspectiveCameraController::OnWindowResizeEvent));
    event_dispatcher.Dispatch<MouseScrolledEvent>(
        BIND_METHOD(PerspectiveCameraController::OnMouseScrolledEvent));
    return false;
  }

  const PerspectiveCamera& GetCamera() const { return camera_; }
  bool OnUpdate(TimeStep time_step);
  bool OnWindowResizeEvent(WindowResizeEvent& event);
  bool OnMouseScrolledEvent(MouseScrolledEvent& event);

 private:
  PerspectiveCamera camera_;
  glm::vec2 move_speed_ = glm::vec2(1.0f);
  float zoom_speed_ = 0.05f;
};

}  // namespace genesis