#pragma once
#include <glm/glm.hpp>

#include "core/component/game_object.h"
#include "core/component/transform.h"
#include "core/renderer/buffer.h"
namespace genesis {
enum class LightType { Directional = 1, Point = 2, Spot = 3 };
class Light : public Component {
 public:
  Light(GameObject *game_object);
  LightType GetLightType() const { return type_; }
  void SetLightType(LightType type) {
    type_ = type;
    ResetUniform();
  }
  glm::vec3 GetDirection() const { return direction_; }
  void SetDirection(glm::vec3 direction) {
    direction_ = direction;
    ResetUniform();
  }
  glm::vec3 GetColor() const { return color_; }
  void SetColor(glm::vec3 color) {
    color_ = color;
    ResetUniform();
  }
  glm::vec3 GetPosition() const {
    auto transform = dynamic_cast<const Transform *>(GetGameObject()->GetComponent("Transform"));
    return transform->GetPosition();
  }
  void SetPosition(glm::vec3 position) {
    auto transform = dynamic_cast<Transform *>(GetGameObject()->GetComponent("Transform"));
    transform->SetPosition(position);
    ResetUniform();
  }
  float GetConstant() const { return constant_; }
  void SetCosntant(float constant) {
    constant_ = constant;
    ResetUniform();
  }
  float GetLinear() const { return linear_; }
  void SetLinear(float linear) {
    linear_ = linear;
    ResetUniform();
  }
  float GetQuadratic() const { return quadratic_; }
  void SetQuadratic(float quadratic) {
    quadratic_ = quadratic;
    ResetUniform();
  }
  std::shared_ptr<const UniformBuffer> GetUniform() const { return ubo_; }

 private:
  void ResetUniform();
  LightType type_ = LightType::Point;
  glm::vec3 direction_ = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec3 color_ = glm::vec3(1.0f, 1.0f, 1.0f);

  float constant_ = 1.0f;
  float linear_ = 0.0f;
  float quadratic_ = 0.0f;

  float cut_off_ = 0.0f;
  float outer_cut_off_ = 0.0f;

  std::shared_ptr<UniformBuffer> ubo_;
};
}  // namespace genesis