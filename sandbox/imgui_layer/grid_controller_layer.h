#pragma once
#include <genesis.h>

#include "imgui_layer.h"
namespace genesis {
class GridControllerLayer : public ImGuiLayer {
  void OnImguiRender() override;
};
}  // namespace genesis