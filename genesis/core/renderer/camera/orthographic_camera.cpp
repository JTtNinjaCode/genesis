#include "orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
namespace genesis {
OrthographicCamera2D::OrthographicCamera2D(float height, float ratio,
                                           float near_plane, float far_plane)
    : height_(height),
      ratio_(ratio),
      near_plane_(near_plane),
      far_plane_(far_plane),
      position_(glm::vec3(0, 0, 1)),
      rotation_radians_(1.0f),
      zoom_level_(1.0f) {
  RecalculateProjectionMatrix();
  RecalculateViewMatrix();
}

void OrthographicCamera2D::RecalculateProjectionMatrix() {
  float zoomed_height = height_ / zoom_level_;
  float zoomed_width = zoomed_height * ratio_;
  projection_ = glm::orthoRH(-zoomed_width / 2.0f, zoomed_width / 2.0f,
                             -zoomed_height / 2.0f, zoomed_height / 2.0f,
                             near_plane_, far_plane_);
}

void OrthographicCamera2D::RecalculateViewMatrix() {
  glm::vec3 world_up(0, 1, 0);
  world_up = glm::rotateZ(world_up, rotation_radians_);
  view_ = glm::lookAtRH(position_, position_ + glm::vec3(0, 0, -1), world_up);
}

}  // namespace genesis