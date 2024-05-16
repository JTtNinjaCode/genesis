#include "imgui_layer/global_layer_controller_layer.h"

#include <imgui.h>
namespace genesis {
LayerContext LayerContext::layer_context;

void genesis::GlobalLayerController::OnImguiRender() {
  ImGui::Begin("Global Layer");
  ImGui::Checkbox("Grid Controller", &LayerContext::layer_context.grid_controller);
  ImGui::End();
}
}  // namespace genesis