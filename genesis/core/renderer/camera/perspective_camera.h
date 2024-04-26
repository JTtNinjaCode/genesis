#pragma once
#include <glm/glm.hpp>

namespace genesis {
class PerspectiveCamera {
 public:
  PerspectiveCamera(float field_of_view, float ratio, float near_plane, float far_plane, glm::vec3 position,
                    glm::vec3 target);

  float GetFieldOfView() const { return field_of_view_; }

  float GetRatio() const { return ratio_; }

  float GetNear() const { return near_; }

  float GetFar() const { return far_; }

  glm::vec3 GetPosition() const { return position_; }

  glm::vec3 GetDirection() const { return direction_; }

  glm::mat4 GetProjection() const { return projection_; }

  glm::mat4 GetView() const { return view_; };

  glm::mat4 GetProjectionView() const { return projection_view_; }

  void SetDirection(glm::vec3 direction) {
    direction_ = glm::normalize(direction);
    RecalculateView();
  }

  void SetFieldOfView(float field_of_view) {
    field_of_view_ = field_of_view;
    RecalculateProjection();
  }

  void SetRatio(float ratio) {
    ratio_ = ratio;
    RecalculateProjection();
  }

  void SetNear(float near_plane) {
    near_ = near_plane;
    RecalculateProjection();
  }

  void SetFar(float far_plane) {
    far_ = far_plane;
    RecalculateProjection();
  }

  void SetPosition(glm::vec3 position) {
    position_ = position;
    RecalculateView();
  }

  void LookAt(glm::vec3 target) {
    direction_ = glm::vec3(target - position_);
    RecalculateView();
  }

 private:
  void RecalculateProjection();
  void RecalculateView();

  float field_of_view_;
  float ratio_;
  float near_;
  float far_;

  glm::mat4 projection_;
  glm::mat4 view_;
  glm::mat4 projection_view_;

  glm::vec3 position_;
  glm::vec3 direction_;
};

}  // namespace genesis
