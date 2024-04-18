#pragma once
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/events/window_event.h"
#include "core/renderer/camera/orthographic_camera.h"
#include "core/time_step.h"
namespace genesis {
class OrthographicCameraController {
 public:
  OrthographicCameraController(float height, float ratio, float near_plane, float far_plane);
  EventState OnEvent(Event& event) {
    EventDispatcher event_dispatcher(event);
    event_dispatcher.Dispatch<WindowResizeEvent>(BIND_METHOD(OrthographicCameraController::OnWindowResizeEvent));
    event_dispatcher.Dispatch<MouseScrolledEvent>(BIND_METHOD(OrthographicCameraController::OnMouseScrolledEvent));
    return EventState::kHandled;
  }

  const OrthographicCamera2D& GetCamera() const { return camera_; }
  bool OnUpdate(TimeStep time_step);
  EventState OnWindowResizeEvent(WindowResizeEvent& event);
  EventState OnMouseScrolledEvent(MouseScrolledEvent& event);

 private:
  OrthographicCamera2D camera_;
  glm::vec2 move_speed_ = glm::vec2(1.0f);
  float zoom_speed_ = 0.05f;
};

}  // namespace genesis