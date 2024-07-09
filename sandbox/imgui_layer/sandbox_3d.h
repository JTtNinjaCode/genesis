#pragma once
#include <genesis.h>
#include <fmod_studio.hpp>

#include "imgui_layer/imgui_layer.h"
using namespace genesis;
class Sandbox3D : public ImGuiLayer {
 public:
  Sandbox3D();

  void OnUpdate(TimeStep time_step) override;
  void OnImguiRender() override;
  EventState OnEvent(Event& event) override;
  EventState OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
  EventState OnWindowResizeEvent(WindowResizeEvent& event);

 private:
  std::shared_ptr<CameraController> camera_3d_;
  std::shared_ptr<Shader> model_shader_;
  std::shared_ptr<Shader> outline_shader;
  std::shared_ptr<UniformBuffer> ubo_;
  std::shared_ptr<Texture2D> fonts_;
  std::shared_ptr<Texture2D> image_;

  Scene scene_;
};
