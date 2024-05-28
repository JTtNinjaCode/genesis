#pragma once
#include <genesis.h>

#include "imgui_layer.h"
namespace genesis {
class Inspector : public ImGuiLayer {
 public:
  Inspector() : ImGuiLayer("Inspector") {}
  void SetGameObject(GameObject* game_object);
  void OnImguiRender() override;

 private:
  GameObject* game_object_ = nullptr;
};

}  // namespace genesis