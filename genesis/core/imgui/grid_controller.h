#pragma once
#include "core/imgui/imgui_layer.h"
namespace genesis {
class GridController :public ImGuiLayer{
  void OnImguiRender() override;
};
}