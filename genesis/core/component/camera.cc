#include "camera.h"

#include <glm/gtx/transform.hpp>

#include "core/component/game_object.h"
#include "core/component/transform.h"
namespace genesis {
using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<Camera>("Camera").constructor<GameObject *>()(rttr::policy::ctor::as_std_shared_ptr);
}
glm::mat4 Camera::GetProjection() const {
  switch (projection_mode_) {
    case ProjectionMode::kPerspective:
      glm::mat4 perspective = glm::perspective(fov_, 1.0f, near_, far_);
      return perspective;
      break;
    case ProjectionMode::kOrthographic:
      glm::mat4 orthographics = glm::orthoRH(-size_, size_, -size_, size_, near_, far_);
      return orthographics;
      break;
  }
}
glm::mat4 Camera::GetView() const {
  auto position = GetPosition();
  glm::mat4 view = glm::lookAtRH(position, position + forward_, glm::vec3(0, 1, 0));
  return view;
}
ProjectionMode Camera::GetProjectionMode() const { return projection_mode_; }
void Camera::SetProjectionMode(ProjectionMode projection_mode) { projection_mode_ = projection_mode; }

void Camera::SetFov(float fov) { fov_ = fov; }
void Camera::SetSize(float size) { size_ = size; }
void Camera::SetFar(float far) { far_ = far; }
void Camera::SetNear(float near) { near_ = near; }
float Camera::GetFov() const { return fov_; }
float Camera::GetSize() const { return size_; }
float Camera::GetFar() const { return far_; }
float Camera::GetNear() const { return near_; }

BackgroundMode Camera::GetBackgroundMode() const { return background_mode_; }
void Camera::SetBackgroundMode(BackgroundMode background_mode) {
  if (skybox_ != nullptr && background_mode == BackgroundMode::kSkybox) {
    background_mode_ = BackgroundMode::kSkybox;
  } else {
    background_mode_ = BackgroundMode::kColor;
  }
}
void Camera::SetSkybox(std::vector<std::filesystem::path> &faces_path) {
  skybox_ = std::make_shared<Skybox>(faces_path);
}
glm::vec3 Camera::GetUp() const { return up_; }
glm::vec3 Camera::GetPosition() const {
  auto transform = dynamic_cast<const Transform *>(GetGameObject()->GetConstComponent("Transform"));
  auto position = transform->GetPosition();
  return position;
}
glm::vec3 Camera::GetForward() const { return forward_; }
glm::vec4 Camera::GetClearColor() const { return clear_color_; }
}  // namespace genesis
