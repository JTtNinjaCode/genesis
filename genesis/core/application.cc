#include "core/application.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "core/audio/audio.h"
#include "core/profiler/profiler.h"
#include "core/renderer/buffer_layout.h"
#include "core/renderer/font.h"
#include "core/renderer/render_command.h"
#include "core/renderer/renderer_3d.h"
#include "platform/glfw_context.h"
namespace genesis {
std::shared_ptr<Application> Application::instance_;

Application::Application() {
  Log::Init();
  GLFWContext::Init();
  window_ = std::shared_ptr<Window>(Window::Create("Genesis", 1000, 1000));

  CORE_ASSERT(!instance_, "Application had exist.");
  instance_.reset(this);

  window_->SetEventListener(BIND_METHOD(Application::OnEventEntryPoint));
  window_->SetVSync(false);
  Profiler::Init();
  Renderer3D::Init();
  Font::Init();
  Skybox::Init();
  AudioManager::Init();
}

Application::~Application() {}

void Application::Run() {
  timer.Start();
  while (running_) {
    TimeStep duration = timer.GetDurationFromLastCall();

    LayerManager::RunBeginCallback();
    for (auto& layer : layer_stack_) {
      layer->OnPreUpdate();
      layer->OnUpdate(duration);
      layer->OnPostUpdate();
    }

    for (auto& layer : layer_stack_) {
      layer->OnPreRender();
      layer->OnRender();
      layer->OnPostRender();
    }
    LayerManager::RunEndCallback();
  }
}

void Application::OnEventEntryPoint(Event& event) {
  EventDispatcher event_dispatcher(event);
  event_dispatcher.Dispatch<WindowCloseEvent>(BIND_METHOD(Application::OnWindowClose));

  for (auto iter = layer_stack_.rbegin(); iter != layer_stack_.rend(); iter++) {
    (*iter)->OnEvent(event);
    if (event.isEventHandled()) break;
  }
}

EventState Application::OnWindowClose(WindowCloseEvent& event) {
  running_ = false;
  return EventState::kHandled;
}

void Application::PushLayer(std::unique_ptr<Layer>&& layer) {
  layer->OnAttach();
  layer_map_[layer->GetName()] = layer.get();
  layer_stack_.PushLayer(std::move(layer));
}

void Application::PushOverLayer(std::unique_ptr<Layer>&& layer) {
  layer->OnAttach();
  layer_map_[layer->GetName()] = layer.get();
  layer_stack_.PushOverLayer(std::move(layer));
}

Layer& Application::GetLayer(const std::string& layer_name) { return *(layer_map_.find(layer_name)->second); }

}  // namespace genesis