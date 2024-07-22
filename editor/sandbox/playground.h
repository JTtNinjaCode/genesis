#pragma once
#include "imgui_layer/imgui_layer.h"
using namespace genesis;
class Playground : public ImGuiLayer {
 public:
  Playground();

  void OnUpdate(TimeStep time_step) override;
  void OnRender() override;
  void OnImguiRender() override;
  EventState OnEvent(Event& event) override;

  Scene scene_;
};
