#include "imgui_layer/global_layer_controller.h"

#include <imgui.h>
namespace genesis {
LayerContext LayerContext::layer_context;

void GlobalLayerController::OnImguiRender() {
  ImGui::Begin("Global Layer");
  ImGui::Checkbox("Grid Controller", &LayerContext::layer_context.grid_controller);
  ImGui::Checkbox("Inspector", &LayerContext::layer_context.inspector);
  ImGui::End();
}
}  // namespace genesis