#include "perspective_camera_controller.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "core/application.h"
#include "core/log/log.h"
namespace genesis {
PerspectiveCameraController::PerspectiveCameraController(float height, float ratio, float near_plane, float far_plane,
                                                         glm::vec3 position, glm::vec3 target)
    : camera_(height, ratio, near_plane, far_plane, position, target) {}

bool PerspectiveCameraController::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  event_dispatcher.Dispatch<WindowResizeEvent>(BIND_METHOD(PerspectiveCameraController::OnWindowResizeEvent));
  event_dispatcher.Dispatch<MouseScrolledEvent>(BIND_METHOD(PerspectiveCameraController::OnMouseScrolledEvent));
  event_dispatcher.Dispatch<MouseMovedEvent>(BIND_METHOD(PerspectiveCameraController::OnMouseMovedEvent));
  return false;
}

bool PerspectiveCameraController::OnUpdate(TimeStep time_step) {
  auto& input = genesis::Input::GetInstance();
  glm::vec3 forward_dir = camera_.GetDirection();
  glm::vec3 right_dir = glm::normalize(glm::cross(camera_.GetDirection(), {0, 1, 0}));

  glm::vec3 new_position = camera_.GetPosition();
  if (input.IsKeyPressed(genesis::Keycode::kKeyW)) {
    new_position += forward_dir * move_speed_.z * time_step.GetSeconds();
  } else if (input.IsKeyPressed(genesis::Keycode::kKeyA)) {
    new_position -= right_dir * move_speed_.x * time_step.GetSeconds();
  } else if (input.IsKeyPressed(genesis::Keycode::kKeyS)) {
    new_position -= forward_dir * move_speed_.z * time_step.GetSeconds();
  } else if (input.IsKeyPressed(genesis::Keycode::kKeyD)) {
    new_position += right_dir * move_speed_.x * time_step.GetSeconds();
  }
  camera_.SetPosition(new_position);
  return false;
}

bool PerspectiveCameraController::OnWindowResizeEvent(WindowResizeEvent& event) {
  camera_.SetRatio(Application::GetApplication().GetWindow().GetWidth() /
                   Application::GetApplication().GetWindow().GetHeight());
  return false;
}

bool PerspectiveCameraController::OnMouseScrolledEvent(MouseScrolledEvent& event) {
  // camera_.SetZoomLevel(camera_.GetZoomLevel() + event.GetYOffset() * zoom_speed_);
  return false;
}

bool PerspectiveCameraController::OnMouseMovedEvent(MouseMovedEvent& event) {
  glm::vec3 world_up_dir = glm::vec3(0, 1, 0);
  glm::vec3 forward_dir = camera_.GetDirection();
  glm::vec3 right_dir = glm::cross(forward_dir, world_up_dir);
  glm::quat quaternion_pitch{
      glm::angleAxis<float>(glm::radians(0.1f) * -rotation_speed_.y * event.GetDeltaY(), right_dir)};
  glm::quat quaternion_yaw{
      glm::angleAxis<float>(glm::radians(0.1f) * -rotation_speed_.x * event.GetDeltaX(), world_up_dir)};

  camera_.SetDirection(quaternion_yaw * quaternion_pitch * forward_dir);

  return false;
}

}  // namespace genesis