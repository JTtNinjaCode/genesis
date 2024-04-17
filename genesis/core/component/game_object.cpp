#include "game_object.h"

#include <rttr/registration.h>
namespace genesis {
using namespace rttr;
Component* GameObject::AddComponent(const std::string& component_name) {
  type t = type::get_by_name(component_name);
  variant var = t.create();
  Component* component = var.get_value<Component*>();
  component->set_game_object(this);
  components_[component_name] = component;
  return component;
}
Component* GameObject::GetComponent(const std::string& component_name) {
  auto result = components_[component_name];
  return result;
}
void GameObject::DeleteComponent(const std::string& component_name) { components_.erase(component_name); }
}  // namespace genesis
