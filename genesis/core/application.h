#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "core/core.h"
#include "core/input/input.h"
#include "core/layer/layer_stack.h"
#include "core/log/log.h"
#include "core/timer.h"
#include "core/window.h"
#include "events/event.h"
#include "events/mouse_event.h"
#include "events/window_event.h"

namespace genesis {

class DLL_API Application {
 public:
  // LayerStack own all layers, LayerMap reference it for random access
  using LayerMap = std::unordered_map<std::string, Layer*>;

  Application();
  virtual ~Application();
  static Application& GetInstance() { return *instance_; }

  Window& GetWindow() { return *window_; }
  void OnEventEntryPoint(Event& event);
  EventState OnWindowClose(WindowCloseEvent& event);
  virtual void Run();

  void PushLayer(std::unique_ptr<Layer>&& layer);
  void PushOverLayer(std::unique_ptr<Layer>&& layer);
  Layer& GetLayer(const std::string& layer_name);

 private:
  Timer timer;
  float last_frame_time_ = 0.0f;
  LayerMap layer_map_;
  LayerManager layer_stack_;

  static std::shared_ptr<Application> instance_;
  bool running_ = true;

  std::shared_ptr<Window> window_;
};

Application* CreateApplication();
};  // namespace genesis
