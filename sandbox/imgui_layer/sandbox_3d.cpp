#include "sandbox_3d.h"

#include <limits>
using namespace genesis;
Sandbox3D::Sandbox3D() {
  auto& app = Application::GetInstance();
  auto& window = app.GetWindow();
  float ratio = window.GetWidth() / window.GetHeight();
  window.EnableCursor(true);

  shader_ = Shader::Create("./assets/shaders/model.vert", "./assets/shaders/model.frag");

  camera_3d_ = std::make_shared<PerspectiveCameraController>(glm::radians(45.0f), ratio, 0.01f, 100.0f,
                                                             glm::vec3(0, 16, 50), glm::vec3(0, 10, 0));
  auto* mesh_filter = dynamic_cast<MeshFilter*>(game_object_.AddComponent("Mesh Filter"));
  mesh_filter->SetModel("./assets/models/Nanosuit/nanosuit.obj");
}

void Sandbox3D::OnUpdate(TimeStep time_step) {
  {
    RenderCommand& render_command = RenderCommand::GetInstanced();
    render_command.SetClearColor({0.8, 0.2, 0.5, 1.0f});
    render_command.Clear();
    auto& renderer_3d = Renderer3D();
    renderer_3d.BeginScene(camera_3d_->GetCamera());
    auto transform = dynamic_cast<Transform*>(game_object_.GetComponent("Transform"));
    if (!transform) {
      return;
    }

    glm::mat4 trans_mat = glm::translate(glm::mat4(1.0f), transform->GetPostiion());
    auto rotation = transform->GetRotation();
    glm::mat4 rotate_mat =
        glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
    glm::mat4 scale_mat = glm::scale(glm::mat4(1.0f), transform->GetScale());
    glm::mat4 model = trans_mat * rotate_mat * scale_mat;

    auto component_model = dynamic_cast<const MeshFilter*>(game_object_.GetComponent("Mesh Filter"));

    renderer_3d.Submit(*shader_, component_model->GetModel(), model);
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
  RenderCommand::GetInstanced().SetViewport(0, 0, event.GetWidth(), event.GetHeight());
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
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGuiIO& io = ImGui::GetIO();
  auto& app = Application::GetInstance();
  io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

  auto transform = dynamic_cast<Transform*>(game_object_.GetComponent("Transform"));
  auto position = transform->GetPostiion();
  auto rotation = transform->GetRotation();
  auto scale = transform->GetScale();
  ImGui::Begin("Components");
  ImGui::Text("Transform");
  ImGui::DragFloat3("Position", glm::value_ptr(position), 1.0f, std::numeric_limits<float>::max(),
                    -std::numeric_limits<float>::max());
  ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 1.0f, std::numeric_limits<float>::max(),
                    -std::numeric_limits<float>::max());
  ImGui::DragFloat3("Scale", glm::value_ptr(scale), 1.0f, 0.0f, std::numeric_limits<float>::max());
  ImGui::End();

  transform->SetPosition(position);
  transform->SetRotation(rotation);
  transform->SetScale(scale);

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  //// Update and Render additional Platform Windows, if use multi viewport, use these code
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}
