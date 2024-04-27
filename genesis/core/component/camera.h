#pragma once
#include <rttr/registration.h>

#include <glm/glm.hpp>

#include "core/component/component.h"
namespace genesis {
enum ProjectionMode { kPerspective, kOrthographic };

class Camera : public Component {
 public:
  Camera() = default;
  ProjectionMode camera_usage;
  glm::mat4 GetProjection() const;
  glm::mat4 GetView() const;
  ProjectionMode GetProjectionMode() const;
  void SetProjectionMode(ProjectionMode projection_mode);
  float GetFov() const;
  void SetFov(float fov);
  float GetSize() const;
  void SetSize(float size);
  //bool OnEvent();

 private:
  void RecalculatePerspectiveMatrix();
  void RecalculateOrthographicMatrix();
  void RecalculateViewMatrix();
  glm::vec3 clear_color_ = glm::vec3(255, 0, 144);
  ProjectionMode projection_mode_ = kPerspective;
  float fov_ = 0.0f;
  float size_ = 0.0f;
  float clipping_plane_near_ = 0.1f;
  float clipping_plane_far_ = 100.0f;
  glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::mat4 perspective_;
  glm::mat4 orthographics_;
  glm::mat4 view_;
};
}  // namespace genesis