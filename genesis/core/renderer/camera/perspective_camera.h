#pragma once
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <utility>
#include <vector>

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
  glm::mat4 GetProjection() const override { return glm::perspective(field_of_view_, ratio_, near_, far_); }
  glm::mat4 GetView() const override { return glm::lookAtRH(position_, position_ + direction_, glm::vec3(0, 1, 0)); };
  glm::vec4 GetClearColor() const override { return clear_color_; }
  void SetDirection(glm::vec3 direction) { direction_ = glm::normalize(direction); }
  void SetClearColor(glm::vec4 clear_color) { clear_color_ = clear_color; }
  void SetFieldOfView(float field_of_view) { field_of_view_ = field_of_view; }
  void SetRatio(float ratio) { ratio_ = ratio; }
  void SetNear(float near_plane) { near_ = near_plane; }
  void SetFar(float far_plane) { far_ = far_plane; }
  void SetPosition(glm::vec3 position) { position_ = position; }
  void LookAt(glm::vec3 target) { direction_ = glm::vec3(target - position_); }
  std::shared_ptr<const Skybox> GetSkybox() const { return skybox_; };
  void SetSkybox(const std::vector<std::filesystem::path>& faces_path) {
    skybox_ = std::make_shared<Skybox>(faces_path);
  };

 private:
  float field_of_view_;
  float ratio_;
  float near_;
  float far_;
  glm::vec3 position_;
  glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::vec4 clear_color_;
  std::shared_ptr<Skybox> skybox_ = nullptr;
};

}  // namespace genesis
