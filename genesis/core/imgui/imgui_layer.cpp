#include "imgui_layer.h"

#pragma warning(push)
#pragma warning(disable : 4005)
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#pragma warning(pop)

#include "core/application.h"
#include "core/events/event.h"
#include "core/events/mouse_event.h"

namespace genesis {
ImGuiLayer::ImGuiLayer() : Layer("imgui layer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate(TimeStep time_step) {}

EventState ImGuiLayer::OnEvent(Event& event) {
  EventDispatcher event_dispathcer(event);
  return EventState::kHandled;
}
void ImGuiLayer::OnRender() { OnImguiRender(); }
void ImGuiLayer::OnImguiRender() {}

void ImGuiLayer::Init(Window& window) {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport
  // / Platform Windows
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags) {
    style.WindowRounding = 20.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer bindings
  GLFWwindow* native_window = static_cast<GLFWwindow*>(window.GetNativeWindow());
  ImGui_ImplGlfw_InitForOpenGL(native_window, true);
  ImGui_ImplOpenGL3_Init("#version 460");
}
void ImGuiLayer::Uninit() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
}  // namespace genesis