#include "imgui_layer.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "core/application.h"
#include "core/core.h"
#include "events/event.h"
#include "events/mouse_event.h"

namespace Genesis {
ImGuiLayer::ImGuiLayer() : Layer("imgui layer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  // ImGuiIO& io = ImGui::GetIO();
  // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  // ImGui_ImplGlfw_InitForOpenGL(&(Application::Get().GetWindow()), true);
  ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate() {
  ImGuiIO& io = ImGui::GetIO();
  auto& app = Application::Get();
  io.DisplaySize =
      ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  bool show = true;
  ImGui::ShowDemoWindow(&show);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void ImGuiLayer::OnEvent(Event& event) {
  EventDispatcher event_dispathcer(event);
  event_dispathcer.Dispatch<MouseButtonPressedEvent>(
      BIND_METHOD(ImGuiLayer::OnMousePressed));
  event_dispathcer.Dispatch<MouseButtonReleasedEvent>(
      BIND_METHOD(ImGuiLayer::OnMouseReleased));
  event_dispathcer.Dispatch<MouseMovedEvent>(
      BIND_METHOD(ImGuiLayer::OnMouseMoved));
  event_dispathcer.Dispatch<MouseScrolledEvent>(
      BIND_METHOD(ImGuiLayer::OnMouseScrolled));
}

bool ImGuiLayer::OnMousePressed(MouseButtonPressedEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDown[event.GetMouseButton()] = true;
  return true;
}

bool ImGuiLayer::OnMouseReleased(MouseButtonReleasedEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDown[event.GetMouseButton()] = false;
  return true;
}

bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.MousePos = ImVec2(event.GetX(), event.GetY());

  return true;
}

bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& event) {
  CORE_LOG_TRACE("{0}", event.ToString());
  ImGuiIO& io = ImGui::GetIO();
  io.MouseWheelH += event.GetXOffset();
  io.MouseWheel += event.GetYOffset();

  return true;
}

}  // namespace Genesis