#pragma once
#include <unordered_map>

#include "game_object.h"
namespace genesis {
class Scene {
 public:
  void AddGameObject(const std::string &object_name);
  void DeleteGameObject(const std::string &object_name);
  GameObject &GetGameObject(const std::string &object_name);
 private:
  std::unordered_map<std::string, GameObject> game_objects;
};
}  // namespace genesis