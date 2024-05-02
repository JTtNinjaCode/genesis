#include "camera.h"

#include <glm/gtx/transform.hpp>

#include "core/component/game_object.h"
#include "core/component/transform.h"
namespace genesis {
using namespace rttr;
RTTR_REGISTRATION { registration::class_<Camera>("Camera").constructor<>()(rttr::policy::ctor::as_std_shared_ptr); }

glm::mat4 Camera::GetProjection() const {
  switch (projection_mode_) {
    case ProjectionMode::kPerspective:
      return perspective_;
      break;
    case ProjectionMode::kOrthographic:
      return orthographics_;
      break;
  }
}
glm::mat4 Camera::GetView() const { return view_; }

glm::mat4 Camera::GetProjectionView() const { return GetProjection() * GetView(); }

ProjectionMode Camera::GetProjectionMode() const { return projection_mode_; }

void Camera::SetProjectionMode(ProjectionMode projection_mode) { projection_mode_ = projection_mode; }

float Camera::GetFov() const { return fov_; }

void Camera::SetFov(float fov) {
  fov_ = fov;
  RecalculatePerspectiveMatrix();
}

float Camera::GetSize() const { return size_; }

void Camera::SetSize(float size) {
  size_ = size;
  RecalculateOrthographicMatrix();
}

float genesis::Camera::GetFar() const { return far_; }

void genesis::Camera::SetFar(float far) { far_ = far; }

float genesis::Camera::GetNear() const { return near_; }

void genesis::Camera::SetNear(float near) { near_ = near; }

void Camera::RecalculatePerspectiveMatrix() { perspective_ = glm::perspective(fov_, 1.0f, near_, far_); }

void Camera::RecalculateOrthographicMatrix() {
  orthographics_ = glm::orthoRH(-size_, size_, -size_, size_, near_, far_);
}

void Camera::RecalculateViewMatrix() {
  auto position = GetPosition();
  view_ = glm::lookAtRH(position, position + direction_, glm::vec3(0, 1, 0));
}

glm::vec3 Camera::GetPosition() const {
  auto transform = dynamic_cast<const Transform*>(GetGameObject()->GetConstComponent("Transform"));
  auto position = transform->GetPosition();
  return position;
}

glm::vec3 Camera::GetDirection() const { return direction_; }
}  // namespace genesis
