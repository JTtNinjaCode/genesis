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

#include <filesystem>
#include <iostream>
#include <memory>

#include "core/renderer/camera/orthographic_camera_controller.h"
#include "core/renderer/renderer_2d.h"
#include "core/renderer/shader_library.h"
#include "platform/render_api/opengl/opengl_shader.h"

class ImGuiLayerImpl : public genesis::ImGuiLayer {
 public:
  ImGuiLayerImpl() {
    texture_ = genesis::Texture2D::Create(
        "./assets/textures/small smoke checkerboard.jpg");
    texture2_ = genesis::Texture2D::Create("./assets/textures/cherno.png");

    auto shader_library = genesis::ShaderLibrary::GetInstance();
    shader_library.AddShader("test", "./assets/shaders/test.vert",
                             "./assets/shaders/test.frag");
    shader_ = shader_library.GetShader("test");

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
    camera_2d_controller_ =
        std::make_shared<genesis::OrthographicCameraController>(3.0f, ratio,
                                                                0.01, 100);
  }

  virtual void OnUpdate(genesis::TimeStep time_step) override {
    std::shared_ptr<genesis::RenderCommand> render_command =
        genesis::RenderCommand::GetInstanced();
    render_command->SetClearColor({0.8, 0.2, 0.5, 1.0f});
    render_command->Clear();

    shader_->Bind();
    dynamic_cast<genesis::OpenGLShader&>(*shader_).SetUniform("u_color",
                                                              square_color);
    dynamic_cast<genesis::OpenGLShader&>(*shader_).SetUniform("tex", 0);

    std::shared_ptr<genesis::Renderer2D> renderer =
        std::make_shared<genesis::Renderer2D>();
    renderer->BeginScene(camera_2d_controller_->GetCamera());
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        texture_->Bind(0);
        renderer->Submit(*shader_, *vao_,
                         glm::translate(glm::scale(glm::mat4(1.0f),
                                                   glm::vec3(0.05, 0.05, 0.05)),
                                        {i + 0.1 * i, j + 0.1 * j, 0.0f}));
        texture2_->Bind(0);
        renderer->Submit(*shader_, *vao_,
                         glm::translate(glm::scale(glm::mat4(1.0f),
                                                   glm::vec3(0.05, 0.05, 0.05)),
                                        {i + 0.1 * i, j + 0.1 * j, 0.0f}));
      }
    }
    renderer->EndScene();

    camera_2d_controller_->OnUpdate(time_step);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("window");
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
    camera_2d_controller_->OnEvent(event);
    genesis::EventDispatcher dispatcher(event);
  }

 private:
  std::shared_ptr<genesis::Shader> shader_;
  std::shared_ptr<genesis::VertexBuffer> vbo_;
  std::shared_ptr<genesis::IndexBuffer> ebo_;
  std::shared_ptr<genesis::VertexArray> vao_;
  std::shared_ptr<genesis::PerspectiveCamera> camera_;
  std::shared_ptr<genesis::OrthographicCameraController> camera_2d_controller_;

  std::shared_ptr<genesis::Texture2D> texture_;
  std::shared_ptr<genesis::Texture2D> texture2_;

  glm::vec3 square_color;
};

class SandBox : public genesis::Application {
 public:
  SandBox() { PushOverLayer(std::make_shared<ImGuiLayerImpl>()); }
  ~SandBox() {}
};

genesis::Application* genesis::CreateApplication() {
  genesis::Log::Init();
  CORE_LOG_WARN("Initialized Log!");

  return new SandBox;
}
