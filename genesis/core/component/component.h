#pragma once
namespace genesis {
class GameObject;
class Component {
 public:
  Component() = default;
  virtual ~Component() {}

  GameObject* GetGameObject() const { return game_object_; }
  void SetGameObject(GameObject* game_object) { game_object_ = game_object; }

 private:
  GameObject* game_object_ = nullptr;
};
}  // namespace genesis
