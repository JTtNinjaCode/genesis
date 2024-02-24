#include "core/application.h"
#include "core/window_factory.h"

namespace genesis {
Application* Application::instance_;

Application::Application()
    : window_(
          std::unique_ptr<Window>(WindowFactory::Create("Genesis", 900, 600))) {
  CORE_ASSERT(!instance_, "Application had exist.");
  instance_ = this;

  window_->SetEventListener(BIND_METHOD(Application::OnEvent));
}

Application::~Application() {}

void Application::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  event_dispatcher.Dispatch<WindowCloseEvent>(
      BIND_METHOD(Application::OnWindowClose));
  event_dispatcher.Dispatch<WindowResizeEvent>(
      BIND_METHOD(Application::OnWindowResize));

  for (auto iter = layer_stack_.rbegin(); iter != layer_stack_.rend(); iter++) {
    (*iter)->OnEvent(event);
    if (event.isEventHandled()) break;
  }
}

bool Application::OnWindowClose(WindowCloseEvent& event) {
  running_ = false;
  return true;
}

bool Application::OnWindowResize(WindowResizeEvent& event) {
  CORE_LOG_TRACE("window resize event:{0}", event.ToString());
  return true;
}

bool Application::OnMouseMoved(MouseMovedEvent& event) {
  CORE_LOG_TRACE("mouse moved event:{0}", event.ToString());
  return true;
}

void Application::PushLayer(Layer* layer) {
  layer_stack_.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverLayer(Layer* layer) {
  layer_stack_.PushOverLayer(layer);
  layer->OnAttach();
}
}  // namespace genesis