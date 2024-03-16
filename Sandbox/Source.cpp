#include <Genesis.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

#include <iostream>
#include <memory>

#include "platform/render_api/opengl/opengl_shader.h"

class ImGuiLayerImpl : public genesis::ImGuiLayer {
 public:
  ImGuiLayerImpl() {
    std::string vertex_source = R"(
        #version 460 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec2 uv;

        uniform mat4 u_view_projection;
        uniform mat4 u_model;

        out vec2 a_uv;
        void main() {
            gl_Position = u_view_projection * u_model * vec4(position, 1.0);
            a_uv = uv;
        }
    )";
    std::string fragment_source = R"(
        #version 460 core
        in vec2 a_uv;
        uniform vec3 u_color;
        out vec4 fragment_color;
        void main() {
            fragment_color = vec4(a_uv.x, a_uv.y, 0.0f, 1.0f);
        }
    )";

    shader_ = genesis::Shader::Create(vertex_source, fragment_source);

    float data[20] = {-0.5, -0.5, 0.0, 0.0, 0.0, 0.5, -0.5, 0.0, 1.0, 0.0,
                      -0.5, 0.5,  0.0, 0.0, 1.0, 0.5, 0.5,  0.0, 1.0, 1.0};
    vbo_ = genesis::VertexBuffer::Create(data, sizeof(data));
    vbo_->Bind();

    unsigned int elements[6] = {0, 1, 2, 1, 2, 3};
    ebo_ = genesis::IndexBuffer::Create(elements, sizeof(elements));
    ebo_->Bind();

    genesis::BufferLayout buffer_layout{{genesis::MathDataType::kFloat3},
                                        {genesis::MathDataType::kFloat2}};
    vao_ = genesis::VertexArray::Create(buffer_layout);
    vao_->AddVertexBuffer(*vbo_);
    vao_->SetIndexBuffer(*ebo_);

    float ratio =
        genesis::Application::GetApplication()->GetWindow().GetWidth() /
        float(genesis::Application::GetApplication()->GetWindow().GetHeight());
    camera_ = std::make_shared<genesis::PerspectiveCamera>(
        glm::radians(45.0f), ratio, 0.1, 100.0, glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0));
  }

  virtual void OnUpdate(genesis::TimeStep time_step) override {
    std::shared_ptr<genesis::RenderCommand> render_command =
        genesis::RenderCommand::GetInstanced();
    render_command->SetClearColor({0.8, 0.2, 0.5, 1.0f});
    render_command->Clear();

    shader_->Bind();
    dynamic_cast<genesis::OpenGLShader&>(*shader_).SetUniform("u_color",
                                                              square_color);

    std::shared_ptr<genesis::Renderer> renderer =
        std::make_shared<genesis::Renderer>();
    renderer->BeginScene(*camera_);

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        renderer->Submit(*shader_, *vao_,
                         glm::translate(glm::scale(glm::mat4(1.0f),
                                                   glm::vec3(0.05, 0.05, 0.05)),
                                        {i + 0.1 * i, j + 0.1 * j, 0.0f}));
      }
    }

    renderer->EndScene();

    auto& input = genesis::Input::GetInstance();
    if (input.IsKeyPressed(genesis::Keycode::kKeyW)) {
      camera_->SetPosition(camera_->GetPosition() +
                           glm::vec3(0.0, 0.0, -1.0) * time_step.GetSeconds());
      camera_->LookAt({0, 0, 0});
    } else if (input.IsKeyPressed(genesis::Keycode::kKeyA)) {
      camera_->SetPosition(camera_->GetPosition() +
                           glm::vec3(-1.0, 0.0, 0.0) * time_step.GetSeconds());
      camera_->LookAt({0, 0, 0});
    } else if (input.IsKeyPressed(genesis::Keycode::kKeyS)) {
      camera_->SetPosition(camera_->GetPosition() +
                           glm::vec3(0.0, 0.0, 1.0) * time_step.GetSeconds());
      camera_->LookAt({0, 0, 0});
    } else if (input.IsKeyPressed(genesis::Keycode::kKeyD)) {
      camera_->SetPosition(camera_->GetPosition() +
                           glm::vec3(1.0, 0.0, 0.0) * time_step.GetSeconds());
      camera_->LookAt({0, 0, 0});
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("window");
    ImGui::ColorEdit3("Squre Color", glm::value_ptr(square_color));
    ImGui::End();

    ImGuiIO& io = ImGui::GetIO();
    auto app = genesis::Application::GetApplication();
    io.DisplaySize = ImVec2((float)app->GetWindow().GetWidth(),
                            (float)app->GetWindow().GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  }

  void OnEvent(genesis::Event& event) override {
    genesis::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<genesis::KeyPressedEvent>(
        BIND_METHOD(ImGuiLayerImpl::OnKeyPressed));
  }

  bool OnKeyPressed(genesis::KeyPressedEvent& event) { return false; }

 private:
  std::shared_ptr<genesis::Shader> shader_;
  std::shared_ptr<genesis::VertexBuffer> vbo_;
  std::shared_ptr<genesis::IndexBuffer> ebo_;
  std::shared_ptr<genesis::VertexArray> vao_;
  std::shared_ptr<genesis::PerspectiveCamera> camera_;

  glm::vec3 square_color;
};

class SandBox : public genesis::Application {
 public:
  SandBox() { PushOverLayer(new ImGuiLayerImpl); }
  ~SandBox() {}
};

genesis::Application* genesis::CreateApplication() {
  genesis::Log::Init();
  CORE_LOG_WARN("Initialized Log!");

  return new SandBox;
}
