#pragma once
#include <glm/glm.hpp>

#include "core/component/component.h"
namespace genesis {
enum class LightType { Directional, Point, Spot };
class Light : public Component {
 public:
  Light() = default;
  LightType GetLightType() const { return type_; }
  void SetLightType(LightType type) { type_ = type; }
  glm::vec3 GetDirection() const { return direction_; }
  void SetDirection(glm::vec3 direction) { direction_ = direction; }
  glm::vec3 GetColor() const { return color_; }
  void SetColor(glm::vec3 color) { color_ = color; }
  glm::vec3 GetPosition() const {
    auto transform = dynamic_cast<const Transform *>(GetGameObject()->GetComponent("Transform"));
    return transform->GetPosition();
  }
  void SetPosition(glm::vec3 position) {
    auto transform = dynamic_cast<const Transform *>(GetGameObject()->GetComponent("Transform"));
    transform->SetPosition(position);
  }
  float GetConstant() const { return constant_; }
  void SetCosntant(float constant) { constant_ = constant; }
  float GetLinear() const { return linear_; }
  void SetLinear(float linear) { linear_ = linear; }
  float GetQuadratic() const { return quadratic_; }
  void SetQuadratic(float quadratic) { quadratic_ = quadratic; }

 private:
  LightType type_;
  glm::vec3 direction_;
  glm::vec3 color_;

  float constant_;
  float linear_;
  float quadratic_;

  float cutOff;
};
}  // namespace genesis