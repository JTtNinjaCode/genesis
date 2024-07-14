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
  Camera(GameObject* game_object) : Component(game_object) {}
  glm::mat4 GetProjection() const override;
  glm::mat4 GetView() const override;
  glm::vec3 GetPosition() const override;
  glm::vec3 GetForward() const override;
  glm::vec3 GetUp() const override;
  glm::vec4 GetClearColor() const override;
  ProjectionMode GetProjectionMode() const;
  void SetProjectionMode(ProjectionMode projection_mode);

  float GetFov() const;
  float GetSize() const;
  float GetFar() const override;
  float GetNear() const override;
  void SetFov(float fov);
  void SetSize(float size);
  void SetFar(float far);
  void SetNear(float near);

  BackgroundMode GetBackgroundMode() const;
  void SetBackgroundMode(BackgroundMode background_mode);
  void SetSkybox(std::vector<std::filesystem::path>& faces_path);
  std::shared_ptr<const Skybox> GetSkybox() const { return skybox_; };
  // bool OnEvent();

 private:
  ProjectionMode projection_mode_ = kPerspective;
  BackgroundMode background_mode_ = kSkybox;
  float fov_ = 0.0f;
  float size_ = 0.0f;
  float near_ = 0.1f;
  float far_ = 100.0f;
  glm::vec3 forward_ = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec4 clear_color_ = glm::vec4(255, 0, 144, 255);
  std::shared_ptr<Skybox> skybox_;
};
}  // namespace genesis