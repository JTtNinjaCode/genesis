#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "core/component/component.h"
namespace genesis {
class GameObject {
 public:
  Component* AddComponent(const std::string& component_name);
  Component* GetComponent(const std::string& component_name);
  void DeleteComponent(const std::string& component_name);

 private:
  std::unordered_map<std::string, Component*> components_;
};

}  // namespace genesis
