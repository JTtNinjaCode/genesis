#include "sandbox_3d.h"

#include <imgui.h>

#include <limits>
using namespace genesis;
Sandbox3D::Sandbox3D() {
  auto& app = Application::GetInstance();
  auto& window = app.GetWindow();
  float ratio = float(window.GetWidth()) / window.GetHeight();
  window.EnableCursor(true);

  shader_ = Shader::Create("./assets/shaders/model.vert", "./assets/shaders/model.frag");

  camera_3d_ = std::make_shared<PerspectiveCameraController>(glm::radians(60.0f), ratio, 0.01f, 300.0f,
                                                             glm::vec3(0, 0, 50), glm::vec3(0, 0, 0));
  camera_3d_->SetClearColor({1.0f, 1.0f, 1.0f, 1.0f});

  auto* mesh_filter = dynamic_cast<MeshFilter*>(model_.AddComponent("Mesh Filter"));
  mesh_filter->SetModel("./assets/models/Nanosuit/nanosuit.obj");

  auto* light = dynamic_cast<Light*>(light_.AddComponent("Light"));
  light->SetColor({0.5f, 0.5f, 0.5f});
  light->SetPosition({0.0f, 30.0f, 30.0f});
  light->SetDirection({1.0f, 1.0f, 1.0f});
  light->SetLightType(LightType::Point);
}

void Sandbox3D::OnUpdate(TimeStep time_step) {
  {
    auto& renderer_3d = Renderer3D();
    auto& camera = camera_3d_->GetCamera();
    renderer_3d.BeginScene(camera);

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
    renderer_3d.Submit(*shader_, component_model->GetModel(), model, component_light, &camera);
    
    
    auto& grid = Grid::GetInstance();
    grid.GetShader().Bind();
    grid.GetShader().SetUniform("u_grid_opacity", grid.GetOpacity());
    grid.GetShader().SetUniform("u_grid_plane_mode", (int)grid.GetGridMode());
    renderer_3d.Submit(grid.GetShader(), grid.GetVertexArray(), {1.0f}, nullptr, &camera);
    renderer_3d.EndScene();

    camera_3d_->OnUpdate(time_step);
  }
}

EventState Sandbox3D::OnKeyPressedEvent(KeyPressedEvent& event) {
  // if (event.GetKeyCode() == Keycode::kKeyEscape) {
  //   Application::GetInstance().GetWindow().EnableCursor(true);
  // }
  return EventState::kHandled;
}

EventState Sandbox3D::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) { return EventState::kHandled; }

EventState Sandbox3D::OnWindowResizeEvent(WindowResizeEvent& event) {
  RenderCommand::GetInstance().SetViewport(0, 0, event.GetWidth(), event.GetHeight());
  return EventState::kHandled;
}

EventState Sandbox3D::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  camera_3d_->OnEvent(event);
  event_dispatcher.Dispatch<KeyPressedEvent>(BIND_METHOD(Sandbox3D::OnKeyPressedEvent));
  event_dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_METHOD(Sandbox3D::OnMouseButtonPressedEvent));
  event_dispatcher.Dispatch<WindowResizeEvent>(BIND_METHOD(Sandbox3D::OnWindowResizeEvent));
  return EventState::kHandled;
}

void Sandbox3D::OnImguiRender() {
  ImGuiIO& io = ImGui::GetIO();
  auto& app = Application::GetInstance();
  io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

  auto transform = dynamic_cast<Transform*>(model_.GetComponent("Transform"));
  auto position = transform->GetPosition();
  auto rotation = transform->GetRotation();
  auto scale = transform->GetScale();
  auto color = camera_3d_->GetClearColor();
  ImGui::Begin("Components");
  ImGui::Text("Transform");
  ImGui::DragFloat3("Position", glm::value_ptr(position), 1.0f, std::numeric_limits<float>::max(),
                    -std::numeric_limits<float>::max());
  ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 1.0f, std::numeric_limits<float>::max(),
                    -std::numeric_limits<float>::max());
  ImGui::DragFloat3("Scale", glm::value_ptr(scale), 1.0f, 0.0f, std::numeric_limits<float>::max());
  ImGui::ColorPicker4("Color", glm::value_ptr(color));
  ImGui::End();

  transform->SetPosition(position);
  transform->SetRotation(rotation);
  transform->SetScale(scale);
  camera_3d_->SetClearColor(color);
}
