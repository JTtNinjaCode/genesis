#pragma once
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/events/window_event.h"
#include "core/renderer/camera/camera.h"
#include "core/time_step.h"
namespace genesis {
class CameraController {
 public:
  CameraController(float height, float ratio, float near_plane, float far_plane, glm::vec3 position, glm::vec3 target);
  const CameraData& GetConstCamera() const { return camera_; }
  CameraData& GetCamera() { return camera_; }

  glm::vec4 GetClearColor() const { return camera_.GetClearColor(); }
  void SetClearColor(glm::vec4 clear_color) { camera_.SetClearColor(clear_color); }
  void SetSkybox(const std::vector<std::filesystem::path>& faces_path) { camera_.SetSkybox(faces_path); };

  void OnUpdate(TimeStep time_step);
  EventState OnEvent(Event& event);
  EventState OnWindowResizeEvent(WindowResizeEvent& event);
  EventState OnMouseScrolledEvent(MouseScrolledEvent& event);
  EventState OnMouseMovedEvent(MouseMovedEvent& event);

 private:
  CameraData camera_;
  glm::vec3 move_speed_ = glm::vec3(30.0f);
  glm::vec2 rotation_speed_ = glm::vec2(1.0f);
  float zoom_speed_ = 0.05f;
};
}  // namespace genesis