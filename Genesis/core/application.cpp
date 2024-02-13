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
}

bool Application::OnWindowClose(WindowCloseEvent& event) {
  running_ = false;
  return true;
}

bool Application::OnWindowResize(WindowResizeEvent& event) {
  CORE_LOG_TRACE("window resize event:{0}", event.ToString());
  return true;
}
}  // namespace Genesis