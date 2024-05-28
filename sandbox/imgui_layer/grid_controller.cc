#include "grid_controller.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "imgui_layer/global_layer_controller.h"
namespace genesis {
void GridController::OnImguiRender() {
  auto &show_grid_controller = LayerContext::layer_context.grid_controller;
  if (show_grid_controller) {
    ImGui::Begin("Grid", &show_grid_controller);
    auto &grid = Grid::GetInstance();
    auto grid_mode = grid.GetGridMode();
    ImGui::Text("Grid Plane");
    ImGui::SameLine();
    ImGui::RadioButton("X", (int *)&grid_mode, (int)GridMode::X);
    ImGui::SameLine();
    ImGui::RadioButton("Y", (int *)&grid_mode, (int)GridMode::Y);
    ImGui::SameLine();
    ImGui::RadioButton("Z", (int *)&grid_mode, (int)GridMode::Z);
    grid.SetGridMode(grid_mode);

    ImGui::Text("Grid Opacity");
    if (ImGui::Button("Disable Grid")) {
      grid.Disable();
    }

    auto grid_opacity = grid.GetOpacity();
    ImGui::DragFloat("Opacity", &grid_opacity, 0.01, 0.0f, 1.0f);
    grid.SetOpacity(grid_opacity);
    ImGui::End();
  }
}
}  // namespace genesis