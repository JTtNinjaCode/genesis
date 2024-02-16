#include "core/application.h"

#include "core/log.h "
#include "core/window_factory.h"

namespace Genesis {
#define BIND_METHOD(method_name) \
  std::bind(&Application::method_name, this, std::placeholders::_1)

Application::Application()
    : window_(
          std::unique_ptr<Window>(WindowFactory::Create("Genesis", 900, 600))) {
  window_->SetEventListener(BIND_METHOD(OnEvent));
}

Application::~Application() {}

void Application::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  event_dispatcher.Dispatch<WindowCloseEvent>(BIND_METHOD(OnWindowClose));
  event_dispatcher.Dispatch<WindowResizeEvent>(BIND_METHOD(OnWindowResize));
  // event_dispatcher.Dispatch<MouseMovedEvent>(BIND_METHOD(OnMouseMoved));
  event_dispatcher.Dispatch<MouseButtonPressedEvent>(
      BIND_METHOD(OnMousePressed));

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

bool Application::OnMousePressed(MouseButtonPressedEvent& event) {
  CORE_LOG_TRACE("mouse pressed event:{0}", event.ToString());
  return true;
}

void Application::PushLayer(Layer* layer) { layer_stack_.PushLayer(layer); }

void Application::PushOverLayer(Layer* layer) {
  layer_stack_.PushOverLayer(layer);
}
}  // namespace Genesis