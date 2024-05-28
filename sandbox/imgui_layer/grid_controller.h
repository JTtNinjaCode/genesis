#pragma once
#include <genesis.h>

#include "imgui_layer.h"
namespace genesis {
class GridController : public ImGuiLayer {
 public:
  GridController() : ImGuiLayer("Grid Controller") {}

  void OnImguiRender() override;
};
}  // namespace genesis