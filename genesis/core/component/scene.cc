#include "scene.h"

namespace genesis {
void Scene::AddGameObject(const std::string &object_name) { 
	game_objects.emplace(object_name, GameObject()); }
void Scene::DeleteGameObject(const std::string &object_name) { game_objects.erase(object_name); }
GameObject &Scene::GetGameObject(const std::string &object_name) { return game_objects[object_name]; }
}  // namespace genesis