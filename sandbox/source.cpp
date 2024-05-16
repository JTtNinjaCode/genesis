#include <core/entry_point.h>
#include <genesis.h>

#include "imgui_layer/grid_controller_layer.h"
#include "imgui_layer/sandbox_3d.h"

using namespace genesis;
class Sandbox : public Application {
 public:
  Sandbox() {
    ImGuiLayer::Init();
    PushOverLayer(std::make_shared<Sandbox3D>());
    PushOverLayer(std::make_shared<GridControllerLayer>());
  }
  ~Sandbox() { ImGuiLayer::Uninit(); }
};

Application* genesis::CreateApplication() { return new Sandbox; }
