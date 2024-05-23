#pragma once
#include <glm/glm.hpp>

#include "core/renderer/skybox.h"
namespace genesis {
class Camera3DInterface {
 public:
  virtual glm::mat4 GetProjection() const = 0;
  virtual glm::mat4 GetView() const = 0;
  virtual glm::vec3 GetPosition() const = 0;
  virtual glm::vec3 GetDirection() const = 0;
  virtual glm::vec4 GetClearColor() const = 0;
  virtual float GetNear() const = 0;
  virtual float GetFar() const = 0;
  virtual std::shared_ptr<const Skybox> GetSkybox() const = 0;
};
}  // namespace genesis