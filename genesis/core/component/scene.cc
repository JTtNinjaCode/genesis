#include "scene.h"

#include "core/log/log.h"
namespace genesis {
void Scene::AddGameObject(const std::string &object_name) {
  CORE_LOG_TRACE("Add New Gameobject:{}", object_name.c_str());
  game_objects.emplace(object_name, GameObject());
}
void Scene::DeleteGameObject(const std::string &object_name) { game_objects.erase(object_name); }
GameObject &Scene::GetGameObject(const std::string &object_name) { return game_objects[object_name]; }
}  // namespace genesis