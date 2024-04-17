#pragma once
#include <rttr/registration.h>
namespace genesis {
class GameObject;
class Component {
 public:
  Component() = default;
  virtual ~Component() {}

  GameObject* game_object() { return game_object_; }
  void set_game_object(GameObject* game_object) { game_object_ = game_object; }

 private:
  GameObject* game_object_ = nullptr;
  RTTR_ENABLE();
};
}  // namespace genesis
