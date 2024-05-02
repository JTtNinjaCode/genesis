#pragma once
#include <glm/glm.hpp>

#include "camera_3d_interface.h"

namespace genesis {
class PerspectiveCamera : public Camera3DInterface {
 public:
  PerspectiveCamera(float field_of_view, float ratio, float near_plane, float far_plane, glm::vec3 position,
                    glm::vec3 target);

  float GetFieldOfView() const { return field_of_view_; }

  float GetRatio() const { return ratio_; }

  float GetNear() const override { return near_; }

  float GetFar() const override { return far_; }

  glm::vec3 GetPosition() const override { return position_; }

  glm::vec3 GetDirection() const override { return direction_; }

  glm::mat4 GetProjection() const override { return projection_; }

  glm::mat4 GetView() const override { return view_; };

  glm::mat4 GetProjectionView() const override { return projection_view_; }

  glm::vec4 GetClearColor() const { return clear_color_; }

  void SetDirection(glm::vec3 direction) {
    direction_ = glm::normalize(direction);
    RecalculateView();
  }

  void SetClearColor(glm::vec4 clear_color) { clear_color_ = clear_color; }

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
  glm::vec4 clear_color_;
};

}  // namespace genesis
