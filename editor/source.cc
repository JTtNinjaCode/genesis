#include <core/entry_point.h>
#include <genesis.h>

#include "imgui_layer/global_layer_controller.h"
#include "imgui_layer/grid_controller.h"
#include "imgui_layer/inspector.h"
#include "sandbox/sandbox_3d.h"

using namespace genesis;
class Sandbox : public Application {
 public:
  Sandbox() {
    ImGuiLayer::Init();
    PushOverLayer(std::make_unique<Sandbox3D>());
    PushOverLayer(std::make_unique<GlobalLayerController>());
    PushOverLayer(std::make_unique<GridController>());
    PushOverLayer(std::make_unique<Inspector>());
  }
  ~Sandbox() { ImGuiLayer::Uninit(); }
};

Application* genesis::CreateApplication() { return new Sandbox; }
