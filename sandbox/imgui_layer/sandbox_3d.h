#pragma once
#include <genesis.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning(pop)

class Sandbox3D : public genesis::ImGuiLayer {
 public:
  Sandbox3D() {
    float ratio = genesis::Application::GetInstance().GetWindow().GetWidth() /
                  float(genesis::Application::GetInstance().GetWindow().GetHeight());
    genesis::Application::GetInstance().GetWindow().EnableCursor(false);
    camera_3d_ = std::make_shared<genesis::PerspectiveCameraController>(glm::radians(45.0f), ratio, 0.01f, 100.0f,
                                                                        glm::vec3(0, 16, 100), glm::vec3(0, 10, 0));
    shader_ = genesis::Shader::Create("./assets/shaders/model.vert", "./assets/shaders/model.frag");

    game_object_.AddComponent("Transform");
    genesis::Model* mesh = dynamic_cast<genesis::Model*>(game_object_.AddComponent("Model"));
    mesh->LoadModel("./assets/models/Nanosuit/nanosuit.obj");
  }

  virtual void OnUpdate(genesis::TimeStep time_step) override {
    {
      genesis::RenderCommand& render_command = genesis::RenderCommand::GetInstanced();
      render_command.SetClearColor({0.8, 0.2, 0.5, 1.0f});
      render_command.Clear();

      auto& renderer_3d = genesis::Renderer3D();
      renderer_3d.BeginScene(camera_3d_->GetCamera());
      auto result = game_object_.GetComponent("Transform");
      genesis::Transform* transform = dynamic_cast<genesis::Transform*>(result); 
      if (!transform) {
        return;
      }

      glm::mat4 trans_mat = glm::translate(glm::mat4(1.0f), transform->position());
      auto rotation = transform->rotation();
      glm::mat4 rotate_mat =
          glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
      glm::mat4 scale_mat = glm::scale(glm::mat4(1.0f), transform->scale());
      glm::mat4 model = trans_mat * rotate_mat * scale_mat;

      genesis::Model* component_model = dynamic_cast<genesis::Model*>(game_object_.GetComponent("Model"));
      if (!component_model) {
        return;
      }

      renderer_3d.Submit(*shader_, *component_model, {1.0f});
      renderer_3d.EndScene();

      camera_3d_->OnUpdate(time_step);

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
    }
  }
  bool OnKeyPressedEvent(genesis::KeyPressedEvent& event) {
    if (event.GetKeyCode() == genesis::Keycode::kKeyEscape) {
      genesis::Application::GetInstance().GetWindow().EnableCursor(true);
    }
    return false;
  }

  bool OnMouseButtonPressedEvent(genesis::MouseButtonPressedEvent& event) {
    if (event.GetMouseButton() == genesis::MouseButton::kButtonLeft) {
      genesis::Application::GetInstance().GetWindow().EnableCursor(false);
    }
    return false;
  }

  bool OnEvent(genesis::Event& event) override {
    camera_3d_->OnEvent(event);
    genesis::EventDispatcher event_dispatcher(event);
    event_dispatcher.Dispatch<genesis::KeyPressedEvent>(BIND_METHOD(Sandbox3D::OnKeyPressedEvent));
    event_dispatcher.Dispatch<genesis::MouseButtonPressedEvent>(BIND_METHOD(Sandbox3D::OnMouseButtonPressedEvent));
    return false;
  }

  void OnImguiRender() override {
    ImGuiIO& io = ImGui::GetIO();
    auto& app = genesis::Application::GetInstance();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

    ImGui::ShowDemoWindow();
    ImGui::Text("Test");

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //   GLFWwindow* backup_current_context = glfwGetCurrentContext();
    //   ImGui::UpdatePlatformWindows();
    //   ImGui::RenderPlatformWindowsDefault();
    //   glfwMakeContextCurrent(backup_current_context);
    // }

    if (io.ConfigFlags) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      glfwMakeContextCurrent(backup_current_context);
    }
  }

 private:
  std::shared_ptr<genesis::PerspectiveCameraController> camera_3d_;
  std::vector<genesis::profile::ProfileResult> profile_results_;
  std::shared_ptr<genesis::Shader> shader_;
  genesis::GameObject game_object_;
};
