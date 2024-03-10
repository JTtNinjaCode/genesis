#include "core/application.h"

#include <iostream>

#include "core/renderer/buffer_layout.h"
namespace genesis {

void APIENTRY DebugOutput(GLenum source, GLenum type, unsigned int id,
                          GLenum severity, GLsizei length, const char* message,
                          const void* userParam);

Application* Application::instance_;

Application::Application()
    : window_(std::shared_ptr<Window>(Window::Create("Genesis", 900, 600))) {
  CORE_ASSERT(!instance_, "Application had exist.");
  instance_ = this;

  window_->SetEventListener(BIND_METHOD(Application::OnEvent));

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(DebugOutput, nullptr);

  float data[18] = {-0.5, -0.5, 0.0,  1.0f, 0.0f, 0.0f, 0.5,  -0.5, 0.0,
                    0.0f, 1.0f, 0.0f, 0.0,  0.5,  0.0,  0.0f, 0.0f, 1.0f};
  vbo_ = VertexBuffer::Create(data, sizeof(data));
  vbo_->Bind();

  unsigned int elements[3] = {0, 1, 2};
  ebo_ = IndexBuffer::Create(elements, sizeof(elements));
  ebo_->Bind();

  BufferLayout buffer_layout{{MathDataType::kFloat3}, {MathDataType::kFloat3}};
  vao_ = VertexArray::Create(buffer_layout);
  vao_->AddVertexBuffer(*vbo_);
  vao_->SetIndexBuffer(*ebo_);
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

void APIENTRY DebugOutput(GLenum source, GLenum type, unsigned int id,
                          GLenum severity, GLsizei length, const char* message,
                          const void* userParam) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " << message << std::endl;

  switch (source) {
    case GL_DEBUG_SOURCE_API:
      std::cout << "Source: API";
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      std::cout << "Source: Window System";
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      std::cout << "Source: Shader Compiler";
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      std::cout << "Source: Third Party";
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      std::cout << "Source: Application";
      break;
    case GL_DEBUG_SOURCE_OTHER:
      std::cout << "Source: Other";
      break;
  }
  std::cout << std::endl;

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      std::cout << "Type: Error";
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      std::cout << "Type: Deprecated Behaviour";
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      std::cout << "Type: Undefined Behaviour";
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      std::cout << "Type: Portability";
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      std::cout << "Type: Performance";
      break;
    case GL_DEBUG_TYPE_MARKER:
      std::cout << "Type: Marker";
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      std::cout << "Type: Push Group";
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      std::cout << "Type: Pop Group";
      break;
    case GL_DEBUG_TYPE_OTHER:
      std::cout << "Type: Other";
      break;
  }
  std::cout << std::endl;

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      std::cout << "Severity: high";
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      std::cout << "Severity: medium";
      break;
    case GL_DEBUG_SEVERITY_LOW:
      std::cout << "Severity: low";
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      std::cout << "Severity: notification";
      break;
  }
  std::cout << std::endl;
  std::cout << std::endl;

  CORE_ASSERT(false, "Opengl Error!");
}

}  // namespace genesis
