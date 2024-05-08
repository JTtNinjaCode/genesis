#pragma once
#include <rttr/registration.h>

#include <glm/glm.hpp>

#include "core/component/component.h"
#include "core/component/game_object.h"
#include "core/renderer/camera/camera_3d_interface.h"
namespace genesis {
enum ProjectionMode { kPerspective, kOrthographic };

class Camera : public Component, Camera3DInterface {
 public:
  Camera(GameObject *game_object) : Component(game_object) {}

  // Inherited via CameraInterface
  glm::mat4 GetProjection() const override;
  glm::mat4 GetView() const override;
  glm::mat4 GetProjectionView() const override;
  glm::vec3 GetPosition() const override;
  glm::vec3 GetDirection() const override;

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
  // bool OnEvent();

 private:
  void RecalculatePerspectiveMatrix();
  void RecalculateOrthographicMatrix();
  void RecalculateViewMatrix();
  glm::vec3 clear_color_ = glm::vec3(255, 0, 144);
  ProjectionMode projection_mode_ = kPerspective;
  float fov_ = 0.0f;
  float size_ = 0.0f;
  float near_ = 0.1f;
  float far_ = 100.0f;
  glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::mat4 perspective_;
  glm::mat4 orthographics_;
  glm::mat4 view_;
};
}  // namespace genesis