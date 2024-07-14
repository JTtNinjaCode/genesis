#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "core/component/component.h"
namespace genesis {

class Transform : public Component {
 public:
  Transform(GameObject* game_object) : Component(game_object), position_({0.0f}), rotation_({0.0f}), scale_({1.0f}) {}
  glm::vec3 GetPosition() const { return position_; }
  glm::vec3 GetRotation() const { return rotation_; }
  glm::vec3 GetScale() const { return scale_; }
  glm::mat4 GetModel() const {
    glm::mat4 result = glm::mat4(1.0f);
    result = glm::translate(result, position_);
    result = glm::rotate(result, glm::radians(rotation_.x), {1, 0, 0});
    result = glm::rotate(result, glm::radians(rotation_.y), {0, 1, 0});
    result = glm::rotate(result, glm::radians(rotation_.z), {0, 0, 1});
    result = glm::scale(result, scale_);
    return result;
  }

  void SetPosition(glm::vec3 position) { position_ = position; }
  void SetRotation(glm::vec3 rotation) { rotation_ = rotation; }
  void SetScale(glm::vec3 scale) { scale_ = scale; }

 private:
  glm::vec3 position_;
  glm::vec3 rotation_;  // degree
  glm::vec3 scale_;
};
}  // namespace genesis
