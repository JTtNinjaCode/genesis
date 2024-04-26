#include "game_object.h"

#include <rttr/registration.h>
namespace genesis {
using namespace rttr;
GameObject::GameObject() { AddComponent("Transform"); }
Component* GameObject::AddComponent(const std::string& component_name) {
  type t = type::get_by_name(component_name);
  variant var = t.create();
  auto component = var.get_value<std::shared_ptr<Component>>();
  component->SetGameObject(this);
  components_[component_name] = component;
  return component.get();
}

const Component* GameObject::GetConstComponent(const std::string& component_name) const {
  auto result = components_.find(component_name);
  if (result != components_.end()) {
    return result->second.get();
  }
  return nullptr;
}

Component* GameObject::GetComponent(const std::string& component_name) {
  auto result = components_.find(component_name);
  if (result != components_.end()) {
    return result->second.get();
  }
  return nullptr;
}

void GameObject::DeleteComponent(const std::string& component_name) { components_.erase(component_name); }
}  // namespace genesis
