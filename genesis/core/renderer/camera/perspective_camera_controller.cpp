#include "perspective_camera_controller.h"

#include <glm/gtx/rotate_vector.hpp>

#include "core/application.h"
namespace genesis {
//PerspectiveCameraController::PerspectiveCameraController(float height,
//                                                          float ratio,
//                                                          float near_plane,
//                                                          float far_plane)
//    : camera_(height, ratio, near_plane, far_plane) {}
//
//bool PerspectiveCameraController::OnUpdate(TimeStep time_step) {
//  auto& input = genesis::Input::GetInstance();
//  glm::vec3 new_position = camera_.GetPosition();
//  if (input.IsKeyPressed(genesis::Keycode::kKeyW)) {
//    new_position += glm::rotateZ(
//        glm::vec3(0.0, 1.0, 0.0) * move_speed_.y * time_step.GetSeconds(),
//        camera_.GetRotationRadians());
//  } else if (input.IsKeyPressed(genesis::Keycode::kKeyA)) {
//    new_position += glm::rotateZ(
//        glm::vec3(-1.0, 0.0, 0.0) * move_speed_.x * time_step.GetSeconds(),
//        camera_.GetRotationRadians());
//  } else if (input.IsKeyPressed(genesis::Keycode::kKeyS)) {
//    new_position += glm::rotateZ(
//        glm::vec3(0.0, -1.0, 0.0) * move_speed_.y * time_step.GetSeconds(),
//        camera_.GetRotationRadians());
//  } else if (input.IsKeyPressed(genesis::Keycode::kKeyD)) {
//    new_position += glm::rotateZ(
//        glm::vec3(1.0, 0.0, 0.0) * move_speed_.x * time_step.GetSeconds(),
//        camera_.GetRotationRadians());
//  }
//  camera_.SetPosition(new_position);
//
//  return false;
//}
//
//bool PerspectiveCameraController::OnWindowResizeEvent(
//    WindowResizeEvent& event) {
//  camera_.SetRatio(Application::GetApplication().GetWindow().GetWidth() /
//                   Application::GetApplication().GetWindow().GetHeight());
//  return false;
//}
//
//bool PerspectiveCameraController::OnMouseScrolledEvent(
//    MouseScrolledEvent& event) {
//  camera_.SetZoomLevel(camera_.GetZoomLevel() +
//                       event.GetYOffset() * zoom_speed_);
//  return false;
//}

}  // namespace genesis