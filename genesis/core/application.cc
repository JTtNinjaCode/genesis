#include "core/application.h"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>

#include "core/profiler/profiler.h"
#include "core/renderer/buffer_layout.h"
#include "core/renderer/font.h"
#include "core/renderer/render_command.h"
#include "core/renderer/renderer_3d.h"
namespace genesis {
std::shared_ptr<Application> Application::instance_;

Application::Application() {
  Log::Init();
  window_ = std::shared_ptr<Window>(Window::Create("Genesis", 1000, 1000));

  CORE_ASSERT(!instance_, "Application had exist.");
  instance_.reset(this);

  window_->SetEventListener(BIND_METHOD(Application::OnEventEntryPoint));
  window_->SetVSync(false);

  Profiler::Init();
  Renderer3D::Init();
  Font::Init();
  Skybox::Init();
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

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    for (auto& layer : layer_stack_) {
      layer->OnRender();
    }
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //// Update and Render additional Platform Windows, if use multi viewport, use these code
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
    window_->OnUpdate();
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