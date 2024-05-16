#pragma once
#include <genesis.h>

#include <unordered_map>

#include "imgui_layer/imgui_layer.h"
namespace genesis {
struct LayerContext {
  static LayerContext layer_context;
  bool grid_controller = true;
};
class GlobalLayerController : public ImGuiLayer {
 public:
  void OnImguiRender() override;
};
}  // namespace genesis