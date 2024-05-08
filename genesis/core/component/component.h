#pragma once
namespace genesis {
class GameObject;
class Component {
 public:
  Component(GameObject* game_object) : game_object_(game_object) {}
  virtual ~Component() {}

  GameObject* GetGameObject() const { return game_object_; }

 private:
  GameObject* game_object_ = nullptr;
};
}  // namespace genesis
