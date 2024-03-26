#pragma once
#include <glm/glm.hpp>
namespace genesis {
class OrthographicCamera2D {
 public:
  OrthographicCamera2D(float height, float ratio, float near_plane,
                       float far_plane);
  glm::mat4 GetProjection() const { return projection_; }
  glm::mat4 GetView() const { return view_; }

  float GetZoomLevel() const { return zoom_level_; }
  void SetZoomLevel(float zoom_level) {
    zoom_level_ = zoom_level;
    RecalculateProjectionMatrix();
  }

  float GetRotationRadians() const { return rotation_radians_; }
  void SetRotation(float radians) {
    rotation_radians_ = radians;
    RecalculateViewMatrix();
  }

  float GetHeight() const { return height_; }
  void SetHeight(float height) {
      height_ = height;
      RecalculateProjectionMatrix();
  }

  void SetRatio(float ratio) {
    ratio_ = ratio_;
    RecalculateProjectionMatrix();
  }
  float GetRatio() const { return ratio_; }

  void SetNear(float near_plane) {
    near_plane_ = near_plane;
    RecalculateProjectionMatrix();
  }
  float GetNear() const { return near_plane_; }

  void SetFar(float far_plane) {
    far_plane_ = far_plane;
    RecalculateProjectionMatrix();
  }
  float GetFar() const { return far_plane_; }

  void SetPosition(glm::vec3 position) {
    position_ = position;
    RecalculateViewMatrix();
  }
  glm::vec3 GetPosition() const { return position_; }

 private:
  void RecalculateProjectionMatrix();
  void RecalculateViewMatrix();

  glm::mat4 projection_;
  glm::mat4 view_;

  glm::vec3 position_;
  float height_;
  float rotation_radians_;
  float near_plane_;
  float far_plane_;
  float ratio_;
  float zoom_level_;
};

}  // namespace genesis