#include "core/application.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <iostream>

#include "core/renderer/buffer_layout.h"
#include "core/renderer/render_command.h"
#
namespace genesis {
std::shared_ptr<Application> Application::instance_;

Application::Application()
    : window_(std::shared_ptr<Window>(Window::Create("Genesis", 900, 600))) {
  CORE_ASSERT(!instance_, "Application had exist.");
  instance_.reset(this);

  window_->SetEventListener(BIND_METHOD(Application::OnEvent));
  window_->SetVSync(true);
}

Application::~Application() {}

void Application::Run() {
  timer.Start();
  while (running_) {
    TimeStep duration = timer.GetDurationFromLastCall();

    // update every layer
    for (auto& layer : layer_stack_) {
      layer->OnUpdate(duration);
    }

    window_->OnUpdate();
  }
}

void Application::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  event_dispatcher.Dispatch<WindowCloseEvent>(
      BIND_METHOD(Application::OnWindowClose));

  for (auto iter = layer_stack_.rbegin(); iter != layer_stack_.rend(); iter++) {
    (*iter)->OnEvent(event);
    if (event.isEventHandled()) break;
  }
}

bool Application::OnWindowClose(WindowCloseEvent& event) {
  running_ = false;
  return true;
}

void Application::PushLayer(std::shared_ptr<Layer> layer) {
  layer_stack_.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverLayer(std::shared_ptr<Layer> layer) {
  layer_stack_.PushOverLayer(layer);
  layer->OnAttach();
}
}  // namespace genesis
