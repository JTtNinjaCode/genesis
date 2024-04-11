#pragma once

#pragma once
#include <genesis.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

class Sandbox3D : public genesis::ImGuiLayer {
 public:
  Sandbox3D() {
    float ratio =
        genesis::Application::GetApplication().GetWindow().GetWidth() /
        float(genesis::Application::GetApplication().GetWindow().GetHeight());
    camera_3d_ = std::make_shared<genesis::PerspectiveCamera>(
        glm::radians(45.0f), ratio, 0.01f, 100.0f, glm::vec3(0, 16, 10),
        glm::vec3(0, 10, 0));
    shader_ = genesis::Shader::Create("./assets/shaders/model.vert",
                                      "./assets/shaders/model.frag");

    model_ = std::make_shared<genesis::Model>(
        "./assets/models/Nanosuit/nanosuit.obj");
  }

  virtual void OnUpdate(genesis::TimeStep time_step) override {
    {
      PROFILE("Hello",
              [&](const genesis::profile::ProfileResult& profile_result) {
                profile_results_.push_back(profile_result);
              });
      profile_results_.clear();
      genesis::RenderCommand& render_command =
          genesis::RenderCommand::GetInstanced();
      render_command.SetClearColor({0.8, 0.2, 0.5, 1.0f});
      render_command.Clear();

      auto& renderer_3d = genesis::Renderer3D();
      renderer_3d.BeginScene(*camera_3d_);
      renderer_3d.Submit(*shader_, *model_, glm::mat4(1.0f));
      renderer_3d.EndScene();

      // camera_3d_->OnUpdate(time_step);

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
    }
  }

  void OnEvent(genesis::Event& event) override {
    // camera_3d_->OnEvent(event);
  }

  void OnImguiRender() override {
    ImGuiIO& io = ImGui::GetIO();
    auto& app = genesis::Application::GetApplication();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),
                            (float)app.GetWindow().GetHeight());

    for (auto& result : profile_results_) {
      ImGui::Text("profiler:%s, time: %f ms", result.name,
                  result.duration.count() * 0.001f);
    }

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
  std::shared_ptr<genesis::PerspectiveCamera> camera_3d_;
  std::vector<genesis::profile::ProfileResult> profile_results_;
  std::shared_ptr<genesis::Model> model_;
  std::shared_ptr<genesis::Shader> shader_;
};
