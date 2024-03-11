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
#include "core/renderer/renderer.h"
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
  virtual void Run();
  void OnEvent(Event& event);
  bool OnWindowClose(WindowCloseEvent& event);
  bool OnWindowResize(WindowResizeEvent& event);
  bool OnMouseMoved(MouseMovedEvent& event);

  void PushLayer(Layer* layer);
  void PushOverLayer(Layer* layer);

 private:
  static Application* instance_;
  bool running_ = true;
  LayerStack layer_stack_;

  std::shared_ptr<Window> window_;

  std::shared_ptr<Shader> shader_;
  std::shared_ptr<VertexBuffer> vbo_;
  std::shared_ptr<IndexBuffer> ebo_;
  std::shared_ptr<VertexArray> vao_;
};

Application* CreateApplication();
};  // namespace genesis
