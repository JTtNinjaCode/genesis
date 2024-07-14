#include "platform/window/glfw_window.h"

#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/events/window_event.h"
#include "core/log/log.h"
#include "core/renderer/graphic_context.h"
#include "platform/glfw_context.h"
#include "platform/input/glfw_input.h"
#include "platform/render_api/opengl/opengl_context.h"

namespace genesis {
GLFWWindow::GLFWWindow(const std::string& title, unsigned int width, unsigned height) {
  window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  context_ = new OpenGLContext(window_);  // window_ contain opengl context
  context_->Init();

  SetVSync(false);

  // set user pointer reference window's data, so that we can get data_
  // in event handle function and callback
  glfwSetWindowUserPointer(window_, &data_);
  glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
    WindowCloseEvent event;
    WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });

  glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int x, int y) {
    WindowResizeEvent event(x, y);
    WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });

  glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x, double y) {
    static double last_x = 0.0, last_y = 0.0;
    static bool first_call = true;
    if (first_call) {
      first_call = false;
      last_x = x;
      last_y = y;
    }
    MouseMovedEvent event(x, y, x - last_x, y - last_y);
    last_x = x;
    last_y = y;
    WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("Event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });

  glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
    WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("Event callback function has not been set yet.");
    }
    const GLFWInput& glfw_input = dynamic_cast<GLFWInput&>(Input::GetInstance());
    if (action == GLFW_PRESS) {
      MouseButtonPressedEvent event(glfw_input.GetGenesisMouseButtonFromGLFWMouseButton(button));
      data.event_listener_(event);  // pass event to Application's method
    } else if (action == GLFW_RELEASE) {
      MouseButtonReleasedEvent event(glfw_input.GetGenesisMouseButtonFromGLFWMouseButton(button));
      data.event_listener_(event);  // pass event to Application's method
    }
  });

  glfwSetScrollCallback(window_, [](GLFWwindow* window, double offset_x, double offset_y) {
    MouseScrolledEvent event(offset_x, offset_y);
    WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });

  glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    const GLFWInput& glfw_input = dynamic_cast<GLFWInput&>(Input::GetInstance());
    if (action == GLFW_PRESS) {
      KeyPressedEvent event(glfw_input.GetGenesisKeycodeFromGLFWKeycode(key));
      data.event_listener_(event);  // pass event to Application's method
    } else if (action == GLFW_RELEASE) {
      KeyReleasedEvent event(glfw_input.GetGenesisKeycodeFromGLFWKeycode(key));
      data.event_listener_(event);  // pass event to Application's method
    }
  });

  glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int character) {
    KeyTypedEvent event(character);
    WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });
}

GLFWWindow::~GLFWWindow() { glfwDestroyWindow(window_); }

void GLFWWindow::OnUpdate() {
  glfwMakeContextCurrent(window_);
  glfwPollEvents();
  context_->SwapBuffers();
}

void* GLFWWindow::GetNativeWindow() { return window_; }

unsigned int GLFWWindow::GetWidth() const {
  int x = 0;
  glfwGetWindowSize(window_, &x, nullptr);
  return x;
}

unsigned int GLFWWindow::GetHeight() const {
  int y = 0;
  glfwGetWindowSize(window_, nullptr, &y);
  return y;
}

void GLFWWindow::SetCursorMode(const CursorMode cursor_mode) {
  if (cursor_mode == CursorMode::kNormal) {
    // visible, cursor motion is not limited in window, but limited in whole screen
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  } else if (cursor_mode == CursorMode::kDisabled) {
    // invisible, cursor motion is not limited in window and whole screen
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
}

void GLFWWindow::SetVSync(bool open) {
  if (open) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  data_.is_vsync_ = open;
}

bool GLFWWindow::IsVSync() const { return data_.is_vsync_; }
}  // namespace genesis