#include "perspective_camera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace genesis {
PerspectiveCamera::PerspectiveCamera(float field_of_view, float ratio,
                                     float near, float far, glm::vec3 position,
                                     glm::vec3 target)
    : projection_(glm::perspective(field_of_view, ratio, near, far)),
      view_(glm::lookAtRH(position, target, glm::vec3(0, 1, 0))),
      position_(position),
      direction_(glm::normalize(target - position)),
      field_of_view_(field_of_view),
      ratio_(ratio),
      near_(near),
      far_(far),
      projection_view_(glm::perspective(field_of_view, ratio, near, far) *
                       glm::lookAtRH(position, target, glm::vec3(0, 1, 0))) {}

void PerspectiveCamera::RecalculateProjection() {
  projection_ = glm::perspective(field_of_view_, ratio_, near_, far_);
  projection_view_ = projection_ * view_;
}

void PerspectiveCamera::RecalculateView() {
  view_ = glm::lookAtRH(position_, position_ + direction_, glm::vec3(0, 1, 0));
  projection_view_ = projection_ * view_;
}

}  // namespace genesis