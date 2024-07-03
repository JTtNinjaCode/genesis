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
  PerspectiveCamera(float field_of_view, float ratio, float near, float far, glm::vec3 position, glm::vec3 target)
      : position_(position),
        forward_(glm::normalize(target - position)),
        field_of_view_(field_of_view),
        ratio_(ratio),
        near_(near),
        far_(far) {}

  float GetFieldOfView() const { return field_of_view_; }
  float GetRatio() const { return ratio_; }
  float GetNear() const override { return near_; }
  float GetFar() const override { return far_; }

  glm::vec3 GetPosition() const override { return position_; }
  glm::vec3 GetForward() const override { return forward_; }
  glm::vec3 GetUp() const override { return up_; }
  glm::mat4 GetProjection() const override { return glm::perspective(field_of_view_, ratio_, near_, far_); }
  glm::mat4 GetView() const override { return glm::lookAtRH(position_, position_ + forward_, up_); };
  glm::vec4 GetClearColor() const override { return clear_color_; }

  void SetPosition(glm::vec3 position) { position_ = position; }
  void SetForward(glm::vec3 forward) { forward_ = glm::normalize(forward); }
  void SetUp(glm::vec3 up) { up_ = up; }

  void SetClearColor(glm::vec4 clear_color) { clear_color_ = clear_color; }
  void SetFieldOfView(float field_of_view) { field_of_view_ = field_of_view; }
  void SetRatio(float ratio) { ratio_ = ratio; }
  void SetNear(float near_plane) { near_ = near_plane; }
  void SetFar(float far_plane) { far_ = far_plane; }
  void LookAt(glm::vec3 target) { forward_ = glm::vec3(target - position_); }
  std::shared_ptr<const Skybox> GetSkybox() const { return skybox_; };
  void SetSkybox(const std::vector<std::filesystem::path>& faces_path) {
    skybox_ = std::make_shared<Skybox>(faces_path);
  };

 private:
  glm::vec3 position_;
  glm::vec3 forward_ = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);

  float field_of_view_;
  float ratio_;
  float near_;
  float far_;

  glm::vec4 clear_color_ = glm::vec4(1.0f);
  std::shared_ptr<Skybox> skybox_ = nullptr;
};

}  // namespace genesis
