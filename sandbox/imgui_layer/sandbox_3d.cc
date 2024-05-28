#include "sandbox_3d.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <limits>

#include "core/renderer/font.h"
#include "imgui_layer/file_dialog.h"
#include "imgui_layer/inspector.h"
using namespace genesis;
Sandbox3D::Sandbox3D() : ImGuiLayer("Sandbox3D") {
  auto& app = Application::GetInstance();
  auto& window = app.GetWindow();
  float ratio = float(window.GetWidth()) / window.GetHeight();
  window.EnableCursor(true);

  std::vector<std::filesystem::path> faces_path({
      "./assets/textures/skybox/right.jpg",
      "./assets/textures/skybox/left.jpg",
      "./assets/textures/skybox/top.jpg",
      "./assets/textures/skybox/bottom.jpg",
      "./assets/textures/skybox/front.jpg",
      "./assets/textures/skybox/back.jpg",
  });
  model_shader_ = Shader::Create("./assets/shaders/model.vert", "./assets/shaders/model.frag");
  outline_shader = Shader::Create("./assets/shaders/outline.vert", "./assets/shaders/outline.frag");

  camera_3d_ = std::make_shared<PerspectiveCameraController>(glm::radians(60.0f), ratio, 0.01f, 300.0f,
                                                             glm::vec3(0, 0, 50), glm::vec3(0, 0, 0));
  camera_3d_->GetCamera().SetSkybox(faces_path);
  camera_3d_->SetClearColor({1.0f, 1.0f, 1.0f, 1.0f});

  scene_.AddGameObject("robot");
  scene_.AddGameObject("light");

  auto& model_ = scene_.GetGameObject("robot");
  auto& light_ = scene_.GetGameObject("light");
  auto* mesh_filter = dynamic_cast<MeshFilter*>(model_.AddComponent("Mesh Filter"));
  mesh_filter->SetModel("./assets/models/Nanosuit/nanosuit.obj");

  auto* light = dynamic_cast<Light*>(light_.AddComponent("Light"));
  light->SetPosition({0.0f, 30.0f, 30.0f});
  light->SetColor({1.0f, 1.0f, 1.0f});
  light->SetDirection({1.0f, 1.0f, 1.0f});
  light->SetLightType(LightType::Point);

  Font::LoadFont("./assets/fonts/SedanSC-Regular.ttf", "SedanSC-Regular", 16);
}

void Sandbox3D::OnUpdate(TimeStep time_step) {
  auto& renderer_3d = Renderer3D();
  auto& camera = camera_3d_->GetCamera();
  renderer_3d.BeginScene(camera);

  auto& model_ = scene_.GetGameObject("robot");
  auto& light_ = scene_.GetGameObject("light");

  auto* light = dynamic_cast<Light*>(light_.GetComponent("Light"));
  light->SetPosition({20.0f, 0.0f, 20.0f});

  auto transform = dynamic_cast<Transform*>(model_.GetComponent("Transform"));
  if (!transform) {
    return;
  }
  glm::mat4 trans_mat = glm::translate(glm::mat4(1.0f), transform->GetPosition());
  auto rotation = transform->GetRotation();
  glm::mat4 rotate_mat =
      glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
  glm::mat4 scale_mat = glm::scale(glm::mat4(1.0f), transform->GetScale());
  glm::mat4 model = trans_mat * rotate_mat * scale_mat;

  auto component_model = dynamic_cast<const MeshFilter*>(model_.GetComponent("Mesh Filter"));
  auto component_light = dynamic_cast<const Light*>(light_.GetComponent("Light"));

  auto& render_command = RenderCommand::GetInstance();
  render_command.SetDrawMode(DrawMode::kFill);

  render_command.SetStencilTest(true);
  render_command.SetStencilFunc(StencilFunc::kAlways, 1, 0xff);
  render_command.SetStencilMask(true);
  renderer_3d.Submit(*model_shader_, component_model->GetModel(), model, component_light, &camera);
  render_command.SetStencilFunc(StencilFunc::kNotEqual, 1, 0xff);
  render_command.SetStencilMask(false);

  render_command.SetDepthTest(false);
  renderer_3d.Submit(*outline_shader, component_model->GetModel(), model, nullptr, nullptr);
  render_command.SetStencilMask(true);
  render_command.SetStencilFunc(StencilFunc::kAlways, 0, 0xff);
  render_command.SetDepthTest(true);

  // Font::GetTexture().Bind(0);
  // renderer_3d.Submit(Font::GetShader(), Font::GetVertexArray(), {1.0f}, nullptr, &camera);

  auto& grid = Grid::GetInstance();
  grid.GetShader().Bind();
  grid.GetShader().SetUniform("u_grid_opacity", grid.GetOpacity());
  grid.GetShader().SetUniform("u_grid_plane_mode", (int)grid.GetGridMode());
  renderer_3d.Submit(grid.GetShader(), grid.GetVertexArray(), {1.0f}, nullptr, &camera);
  renderer_3d.EndScene();

  camera_3d_->OnUpdate(time_step);
}

EventState Sandbox3D::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) { return EventState::kHandled; }

EventState Sandbox3D::OnWindowResizeEvent(WindowResizeEvent& event) {
  RenderCommand::GetInstance().SetViewport(0, 0, event.GetWidth(), event.GetHeight());
  return EventState::kHandled;
}

EventState Sandbox3D::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  camera_3d_->OnEvent(event);
  event_dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_METHOD(Sandbox3D::OnMouseButtonPressedEvent));
  event_dispatcher.Dispatch<WindowResizeEvent>(BIND_METHOD(Sandbox3D::OnWindowResizeEvent));
  return EventState::kHandled;
}

void Sandbox3D::OnImguiRender() {
  ImGuiIO& io = ImGui::GetIO();
  auto& app = Application::GetInstance();
  io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

  auto& model = scene_.GetGameObject("robot");
  dynamic_cast<genesis::Inspector&>(app.GetLayer("Inspector")).SetGameObject(&model);
}
