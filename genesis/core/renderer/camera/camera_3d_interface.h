#pragma once
#include <glm/glm.hpp>
namespace genesis {
class Camera3DInterface {
 public:
  virtual glm::mat4 GetProjection() const = 0;
  virtual glm::mat4 GetView() const = 0;
  virtual glm::mat4 GetProjectionView() const = 0;
  virtual glm::vec3 GetPosition() const = 0;
  virtual glm::vec3 GetDirection() const = 0;
  virtual float GetNear() const = 0;
  virtual float GetFar() const = 0;
};
}  // namespace genesis