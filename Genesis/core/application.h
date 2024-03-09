#pragma once
#pragma warning(push)
#pragma warning(disable : 4005)
#include <glad/glad.h>
#pragma warning(pop)

#include <functional>
#include <memory>

#include "core/core.h"
#include "core/input.h"
#include "core/layer_stack.h"
#include "core/log.h"
#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertex_array.h"
#include "core/window.h"
#include "events/event.h"
#include "events/mouse_event.h"
#include "events/window_event.h"
namespace genesis {



class DLL_API Application {
 public:
  Application();
  virtual ~Application();
  static Application& Get() { return *instance_; }

  Window& GetWindow() { return *window_; }
  virtual void Run() {
    std::string vertex_source = R"(
        #version 460 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 color;
        out vec3 v_color;
        void main() {
            gl_Position = vec4(position, 1.0);
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


    shader_ = std::make_unique<Shader>(vertex_source, fragment_source);

    while (running_) {
      glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      shader_->Bind();
      vao_->Bind();
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

      for (auto& layer : layer_stack_) {
        layer->OnUpdate();
      }

      window_->OnUpdate();
    }
  }
  void OnEvent(Event& event);
  bool OnWindowClose(WindowCloseEvent& event);
  bool OnWindowResize(WindowResizeEvent& event);
  bool OnMouseMoved(MouseMovedEvent& event);

  void PushLayer(Layer* layer);
  void PushOverLayer(Layer* layer);

 private:
  static Application* instance_;
  bool running_ = true;
  std::unique_ptr<Window> window_;
  LayerStack layer_stack_;

  std::shared_ptr<Shader> shader_;
  std::shared_ptr<VertexBuffer> vbo_;
  std::shared_ptr<IndexBuffer> ebo_;
  std::shared_ptr<VertexArray> vao_;
};

Application* CreateApplication();
};  // namespace genesis
