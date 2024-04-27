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

ProjectionMode genesis::Camera::GetProjectionMode() const { return projection_mode_; }

void genesis::Camera::SetProjectionMode(ProjectionMode projection_mode) { projection_mode_ = projection_mode; }

float genesis::Camera::GetFov() const { return fov_; }

void Camera::SetFov(float fov) {
  fov_ = fov;
  RecalculatePerspectiveMatrix();
}

float genesis::Camera::GetSize() const { return size_; }

void genesis::Camera::SetSize(float size) {
  size_ = size;
  RecalculateOrthographicMatrix();
}

void genesis::Camera::RecalculatePerspectiveMatrix() {
  perspective_ = glm::perspective(fov_, 1.0f, clipping_plane_near_, clipping_plane_far_);
}

void genesis::Camera::RecalculateOrthographicMatrix() {
  orthographics_ = glm::orthoRH(-size_, size_, -size_, size_, clipping_plane_near_, clipping_plane_far_);
}

void genesis::Camera::RecalculateViewMatrix() {
  auto transform = dynamic_cast<const Transform*>(GetGameObject()->GetConstComponent("Transform"));
  auto position = transform->GetPostiion();
  view_ = glm::lookAtRH(position, position + direction_, glm::vec3(0, 1, 0));
}
}  // namespace genesis