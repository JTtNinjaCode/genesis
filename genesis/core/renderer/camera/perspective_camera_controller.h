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
  const PerspectiveCamera& GetCamera() const { return camera_; }

  bool OnUpdate(TimeStep time_step);
  bool OnEvent(Event& event);
  bool OnWindowResizeEvent(WindowResizeEvent& event);
  bool OnMouseScrolledEvent(MouseScrolledEvent& event);
  bool OnMouseMovedEvent(MouseMovedEvent& event);

 private:
  PerspectiveCamera camera_;
  glm::vec3 move_speed_ = glm::vec3(30.0f);
  glm::vec2 rotation_speed_ = glm::vec2(1.0f);
  float zoom_speed_ = 0.05f;
};

}  // namespace genesis