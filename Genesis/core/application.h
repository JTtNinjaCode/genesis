#pragma once
#include <GLFW/glfw3.h>

#include <functional>
#include <memory>

#include "core/core.h"
#include "core/window.h"
#include "events/event.h"
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

      window_->OnUpdate();
    }
  }
  void OnEvent(Event& event);
  bool OnWindowClose(WindowCloseEvent& event);
  bool OnWindowResize(WindowResizeEvent& event);

 private:
  bool running_ = true;
  std::unique_ptr<Window> window_;
};

std::unique_ptr<Application> CreateApplication();
};  // namespace Genesis
