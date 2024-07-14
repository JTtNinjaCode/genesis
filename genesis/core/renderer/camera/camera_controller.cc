#include "camera_controller.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "core/application.h"
#include "core/log/log.h"
namespace genesis {
CameraController::CameraController(float height, float ratio, float near_plane, float far_plane, glm::vec3 position,
                                   glm::vec3 target)
    : camera_(height, ratio, near_plane, far_plane, position, target) {}

EventState CameraController::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  event_dispatcher.Dispatch<WindowResizeEvent>(BIND_METHOD(CameraController::OnWindowResizeEvent));
  event_dispatcher.Dispatch<MouseScrolledEvent>(BIND_METHOD(CameraController::OnMouseScrolledEvent));
  event_dispatcher.Dispatch<MouseMovedEvent>(BIND_METHOD(CameraController::OnMouseMovedEvent));
  return EventState::kHandled;
}

void CameraController::OnUpdate(TimeStep time_step) {}

EventState CameraController::OnWindowResizeEvent(WindowResizeEvent& event) {
  camera_.SetRatio((float)event.GetHeight() / event.GetWidth());
  return EventState::kHandled;
}

EventState CameraController::OnMouseScrolledEvent(MouseScrolledEvent& event) {
  glm::vec3 new_position = camera_.GetPosition();
  glm::vec3 forward_dir = camera_.GetForward();
  auto& input = genesis::Input::GetInstance();
  new_position += (float)event.GetOffsetY() * forward_dir * 1.5f;
  camera_.SetPosition(new_position);
  return EventState::kHandled;
}

EventState CameraController::OnMouseMovedEvent(MouseMovedEvent& event) {
  auto& input = genesis::Input::GetInstance();
  glm::vec3 forward_dir = camera_.GetForward();
  glm::vec3 world_up_dir = glm::vec3(0, 1, 0);
  glm::vec3 right_dir = glm::normalize(glm::cross(forward_dir, world_up_dir));
  glm::vec3 up_dir = glm::normalize(glm::cross(right_dir, forward_dir));
  glm::vec3 new_position = camera_.GetPosition();
  if (input.IsMousePressed(genesis::MouseButton::kButtonMiddle)) {
    new_position -= (float)event.GetDeltaX() * right_dir * 0.05f;
    new_position += (float)event.GetDeltaY() * up_dir * 0.05f;
  } else if (input.IsMousePressed(genesis::MouseButton::kButtonRight)) {
    glm::quat quaternion_pitch{
        glm::angleAxis<float>(glm::radians(0.1f) * -rotation_speed_.y * event.GetDeltaY(), right_dir)};
    glm::quat quaternion_yaw{
        glm::angleAxis<float>(glm::radians(0.1f) * -rotation_speed_.x * event.GetDeltaX(), world_up_dir)};
    camera_.SetForward(quaternion_yaw * quaternion_pitch * forward_dir);
  }
  camera_.SetPosition(new_position);
  return EventState::kHandled;
}

}  // namespace genesis