#pragma once
#include <rttr/registration.h>

#include <glm/glm.hpp>

#include "core/component/component.h"
#include "core/component/game_object.h"
#include "core/renderer/camera/camera_3d_interface.h"
#include "core/renderer/skybox.h"
namespace genesis {
enum ProjectionMode { kPerspective, kOrthographic };
enum BackgroundMode { kSkybox, kColor };

class Camera : public Component, Camera3DInterface {
 public:
  Camera(GameObject *game_object) : Component(game_object) {}
  glm::mat4 GetProjection() const override;
  glm::mat4 GetView() const override;
  glm::vec3 GetPosition() const override;
  glm::vec3 GetDirection() const override;
  glm::vec4 GetClearColor() const override;
  ProjectionMode GetProjectionMode() const;
  void SetProjectionMode(ProjectionMode projection_mode);
  float GetFov() const;
  void SetFov(float fov);
  float GetSize() const;
  void SetSize(float size);
  float GetFar() const override;
  void SetFar(float far);
  float GetNear() const override;
  void SetNear(float near);
  BackgroundMode GetBackgroundMode() const;
  void SetBackgroundMode(BackgroundMode background_mode);
  void SetSkybox(std::vector<std::filesystem::path> &faces_path);
  std::shared_ptr<const Skybox> GetSkybox() const { return skybox_; };
  // bool OnEvent();

 private:
  ProjectionMode projection_mode_ = kPerspective;
  BackgroundMode background_mode_ = BackgroundMode::kSkybox;
  float fov_ = 0.0f;
  float size_ = 0.0f;
  float near_ = 0.1f;
  float far_ = 100.0f;
  glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::vec4 clear_color_ = glm::vec4(255, 0, 144, 255);
  std::shared_ptr<Skybox> skybox_;
};
}  // namespace genesis