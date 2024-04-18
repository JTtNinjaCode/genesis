#pragma once
#include <genesis.h>

#include <iostream>
#pragma warning(push)
#pragma warning(disable : 4005)
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#pragma warning(pop)

using namespace genesis;
class Sandbox2D : public genesis::ImGuiLayer {
 public:
  Sandbox2D() {
    float ratio = genesis::Application::GetInstance().GetWindow().GetWidth() /
                  float(genesis::Application::GetInstance().GetWindow().GetHeight());
    camera_2d_controller_ = std::make_shared<genesis::OrthographicCameraController>(3.0f, ratio, 0.01f, 100.0f);
    texture_ = genesis::Texture2D::Create("./assets/textures/small smoke checkerboard.jpg");
  }

  virtual void OnUpdate(genesis::TimeStep time_step) override {
    {
      std::cout << glm::to_string(glm::faceforward(glm::vec3{10, 20, 10}, glm::vec3{0, 3, 0}, glm::vec3{0, -1, 0}))
                << std::endl;
      PROFILE("Hello", [&](const genesis::profile::ProfileResult& profile_result) {
        profile_results_.push_back(profile_result);
      });
      profile_results_.clear();
      genesis::RenderCommand& render_command = genesis::RenderCommand::GetInstanced();
      render_command.SetClearColor({0.8, 0.2, 0.5, 1.0f});
      render_command.Clear();

      auto& renderer_2d = genesis::Renderer2D::GetInstanced();
      renderer_2d.BeginScene(camera_2d_controller_->GetCamera());
      renderer_2d.DrawQuad({0.2, 0.2, -20.0f}, {1, 1}, rotate_radians_, *texture_);
      renderer_2d.DrawQuad({0.0, 0.0, -10.0f}, {1, 1}, rotate_radians_, {1.0, 1.0, 0.0, 1.0});
      renderer_2d.DrawQuad({-0.2, -0.2, -15.0f}, {1, 1}, rotate_radians_, *texture_, {0.8, 0.8, 1.0, 1.0});
      renderer_2d.EndScene();

      camera_2d_controller_->OnUpdate(time_step);

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
    }
  }

EventState OnEvent(genesis::Event& event) override {
    camera_2d_controller_->OnEvent(event);
  return EventState::kHandled;
  }

  void OnImguiRender() override {
    ImGuiIO& io = ImGui::GetIO();
    auto& app = genesis::Application::GetInstance();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

    ImGui::ColorEdit3("color editor", glm::value_ptr(square_color_));
    ImGui::DragFloat("float", &rotate_radians_, 0.01);
    for (auto& result : profile_results_) {
      ImGui::Text("profiler:%s, time: %f ms", result.name, result.duration.count() * 0.001f);
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
  std::shared_ptr<genesis::OrthographicCameraController> camera_2d_controller_;
  float rotate_radians_ = 0.0f;
  std::shared_ptr<genesis::Texture2D> texture_;
  glm::vec3 square_color_ = glm::vec3(1.0f);
  std::vector<genesis::profile::ProfileResult> profile_results_;
};