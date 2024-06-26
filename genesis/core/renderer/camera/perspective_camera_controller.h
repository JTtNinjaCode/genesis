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
  PerspectiveCameraController(float height, float ratio, float near_plane, float far_plane, glm::vec3 position,
                              glm::vec3 target);
  PerspectiveCamera& GetCamera() { return camera_; }

  glm::vec4 GetClearColor() const { return camera_.GetClearColor(); }
  void SetClearColor(glm::vec4 clear_color) { camera_.SetClearColor(clear_color); }

  void OnUpdate(TimeStep time_step);
  EventState OnEvent(Event& event);
  EventState OnWindowResizeEvent(WindowResizeEvent& event);
  EventState OnMouseScrolledEvent(MouseScrolledEvent& event);
  EventState OnMouseMovedEvent(MouseMovedEvent& event);

 private:
  PerspectiveCamera camera_;
  glm::vec3 move_speed_ = glm::vec3(30.0f);
  glm::vec2 rotation_speed_ = glm::vec2(1.0f);
  float zoom_speed_ = 0.05f;
};
}  // namespace genesis