#include <Genesis.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#pragma warning(pop)

#include <iostream>
#include <memory>

class ExampleLayer : public genesis::Layer {
 public:
  ExampleLayer() : Layer("example layer.") {
    std::string vertex_source = R"(
        #version 460 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 color;
        uniform mat4 u_view_projection;
        out vec3 v_color;
        void main() {
            gl_Position = u_view_projection * vec4(position, 1.0);
            v_color = color;
        }
    )";
    std::string fragment_source = R"(
        #version 460 core
        in vec3 v_color;
        out vec4 fragment_color;
        void main() {
            fragment_color = vec4(v_color, 1.0f);
        }
    )";
    shader_ = genesis::Shader::Create(vertex_source, fragment_source);

    float data[18] = {-0.5, -0.5, 0.0,  1.0f, 0.0f, 0.0f, 0.5,  -0.5, 0.0,
                      0.0f, 1.0f, 0.0f, 0.0,  0.5,  0.0,  0.0f, 0.0f, 1.0f};
    vbo_ = genesis::VertexBuffer::Create(data, sizeof(data));
    vbo_->Bind();

    unsigned int elements[3] = {0, 1, 2};
    ebo_ = genesis::IndexBuffer::Create(elements, sizeof(elements));
    ebo_->Bind();

    genesis::BufferLayout buffer_layout{{genesis::MathDataType::kFloat3},
                                        {genesis::MathDataType::kFloat3}};
    vao_ = genesis::VertexArray::Create(buffer_layout);
    vao_->AddVertexBuffer(*vbo_);
    vao_->SetIndexBuffer(*ebo_);

    camera_ = std::make_shared<genesis::PerspectiveCamera>(
        glm::radians(45.0f), 1.0f, 0.1, 100.0, glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0));
  }

  virtual void OnUpdate() override {
    std::shared_ptr<genesis::RenderCommand> render_command =
        genesis::RenderCommand::GetInstanced();
    render_command->SetClearColor({1.0f, 0.0f, 1.0f, 1.0f});
    render_command->Clear();

    std::shared_ptr<genesis::Renderer> renderer =
        std::make_shared<genesis::Renderer>();
    renderer->BeginScene(*camera_);
    renderer->Submit(*shader_,
                     *vao_);  // function overloading, depend on vao, or mesh
    renderer->EndScene();

    auto& input = genesis::Input::GetInstance();
    if (input.IsKeyPressed(genesis::Keycode::kKeyW)) {
      camera_->SetPosition(camera_->GetPosition() + glm::vec3(0.0, 0, -0.01));
      camera_->LookAt({0, 0, 0});
    } else if (input.IsKeyPressed(genesis::Keycode::kKeyA)) {
      camera_->SetPosition(camera_->GetPosition() + glm::vec3(-0.01, 0, 0));
      camera_->LookAt({0, 0, 0});
    } else if (input.IsKeyPressed(genesis::Keycode::kKeyS)) {
      camera_->SetPosition(camera_->GetPosition() + glm::vec3(0, 0, 0.01));
      camera_->LookAt({0, 0, 0});
    } else if (input.IsKeyPressed(genesis::Keycode::kKeyD)) {
      camera_->SetPosition(camera_->GetPosition() + glm::vec3(0.01, 0, 0));
      camera_->LookAt({0, 0, 0});
    }
  }

 private:
  std::shared_ptr<genesis::Shader> shader_;
  std::shared_ptr<genesis::VertexBuffer> vbo_;
  std::shared_ptr<genesis::IndexBuffer> ebo_;
  std::shared_ptr<genesis::VertexArray> vao_;
  std::shared_ptr<genesis::PerspectiveCamera> camera_;

  void OnAttach() override {}
  void OnDetach() override {}
  void OnEvent(genesis::Event& event) override {
    genesis::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<genesis::KeyPressedEvent>(
        BIND_METHOD(ExampleLayer::OnKeyPressed));
  }

  bool OnKeyPressed(genesis::KeyPressedEvent& event) { return false; }
};

class ImGuiLayerImpl : public genesis::ImGuiLayer {
  virtual void OnUpdate() override {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("window");
    ImGui::Text("Test~");
    ImGui::End();

    ImGuiIO& io = ImGui::GetIO();
    genesis::Application& app = genesis::Application::Get();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),
                            (float)app.GetWindow().GetHeight());

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
};

class SandBox : public genesis::Application {
 public:
  SandBox() {
    PushOverLayer(new ExampleLayer);
    PushOverLayer(new ImGuiLayerImpl);
  }
  ~SandBox() {}
};

genesis::Application* genesis::CreateApplication() {
  genesis::Log::Init();
  CORE_LOG_WARN("Initialized Log!");

  return new SandBox;
}
