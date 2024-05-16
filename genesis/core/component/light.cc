#include "light.h"

#include <rttr/registration.h>

#include <glm/gtc/type_ptr.hpp>

#include "core/component/game_object.h"
namespace genesis {
using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<Light>("Light").constructor<GameObject *>()(rttr::policy::ctor::as_std_shared_ptr);
}

Light::Light(GameObject *game_object) : Component(game_object) {
  size_t size = 0;
  size += 16;
  size += 16;
  size += 16;
  size += 16;
  size += 4;
  size += 4;
  size += 4;
  size += 4;
  size += 4;
  ubo_ = UniformBuffer::Create(nullptr, size);
}

void Light::ResetUniform() {
  size_t size = 0;
  auto transform = dynamic_cast<const Transform *>(GetGameObject()->GetComponent("Transform"));
  glm::vec3 position = transform->GetPosition();
  ubo_->SubData(&type_, sizeof(int), size);
  size += 16;
  ubo_->SubData(glm::value_ptr(position), sizeof(glm::vec3), size);
  size += 16;
  ubo_->SubData(glm::value_ptr(direction_), sizeof(glm::vec3), size);
  size += 16;
  ubo_->SubData(glm::value_ptr(color_), sizeof(glm::vec3), size);
  size += 12;
  ubo_->SubData(&constant_, sizeof(float), size);
  size += 4;
  ubo_->SubData(&linear_, sizeof(float), size);
  size += 4;
  ubo_->SubData(&quadratic_, sizeof(float), size);
  size += 4;
  ubo_->SubData(&cut_off_, sizeof(float), size);
  size += 4;
  ubo_->SubData(&outer_cut_off_, sizeof(float), size);
}

}  // namespace genesis