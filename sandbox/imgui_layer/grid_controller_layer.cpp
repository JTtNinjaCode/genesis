#include "grid_controller_layer.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "core/log/log.h"
#include "core/renderer/grid.h"
namespace genesis {
void GridControllerLayer::OnImguiRender() {
  static bool show = true;  // TODO: build All Layer Context
  if (show) {
    ImGui::Begin("Grid", &show);
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