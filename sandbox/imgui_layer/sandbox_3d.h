#pragma once
#include <genesis.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning(pop)
using namespace genesis;
class Sandbox3D : public ImGuiLayer {
 public:
  Sandbox3D();

  void OnUpdate(TimeStep time_step) override;
  void OnImguiRender() override;
  EventState OnEvent(Event& event) override;
  EventState OnKeyPressedEvent(KeyPressedEvent& event);
  EventState OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
  EventState OnWindowResizeEvent(WindowResizeEvent& event);

 private:
  std::shared_ptr<PerspectiveCameraController> camera_3d_;
  std::vector<profile::ProfileResult> profile_results_;
  std::shared_ptr<Shader> shader_;
  std::shared_ptr<Shader> shader2_;
  std::shared_ptr<VertexArray> vertex_array_;
  GameObject model_;
  GameObject light_;
};
