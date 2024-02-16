#pragma once
#include <glad/glad.h>

#include <functional>
#include <memory>

#include "core/core.h"
#include "core/layer_stack.h"
#include "core/window.h"
#include "events/event.h"
#include "events/mouse_event.h"
#include "events/window_event.h"
namespace Genesis {
class DLL_API Application {
 public:
  Application();
  virtual ~Application();

  virtual void Run() {
    while (running_) {
      glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

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
  bool OnMousePressed(MouseButtonPressedEvent& event);

  void PushLayer(Layer* layer);
  void PushOverLayer(Layer* layer);

 private:
  bool running_ = true;
  std::unique_ptr<Window> window_;
  LayerStack layer_stack_;
};

std::unique_ptr<Application> CreateApplication();
};  // namespace Genesis
