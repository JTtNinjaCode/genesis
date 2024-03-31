#pragma once
#include <functional>
#include <memory>

#include "core/core.h"
#include "core/input.h"
#include "core/layer/layer_stack.h"
#include "core/log/log.h"
#include "core/renderer/buffer.h"
#include "core/renderer/camera/perspective_camera.h"
#include "core/renderer/renderer.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertex_array.h"
#include "core/time_step.h"
#include "core/timer.h"
#include "core/window.h"
#include "events/event.h"
#include "events/mouse_event.h"
#include "events/window_event.h"

namespace genesis {

class DLL_API Application {
 public:
  Application();
  virtual ~Application();
  static Application& GetApplication() { return *instance_; }

  Window& GetWindow() { return *window_; }
  virtual void Run();
  void OnEvent(Event& event);
  bool OnWindowClose(WindowCloseEvent& event);
  bool OnWindowResize(WindowResizeEvent& event);

  void PushLayer(std::shared_ptr<Layer> layer);
  void PushOverLayer(std::shared_ptr<Layer> layer);

 private:
  Timer timer;
  static std::shared_ptr<Application> instance_;
  bool running_ = true;
  LayerStack layer_stack_;

  std::shared_ptr<Window> window_;

  float last_frame_time_ = 0.0f;
};

Application* CreateApplication();
};  // namespace genesis
