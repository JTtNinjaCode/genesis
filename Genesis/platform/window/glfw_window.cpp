#include "glfw_window.h"

#include <glad/glad.h>

#include "core/log.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
#include "events/window_event.h"

namespace Genesis {
bool GLFWWindow::is_glfw_initialized_ = false;

static void GLFWErrorCallback(int error_code, const char* description) {
  CORE_LOG_WARN("glfw Error:[{0}], {1}", error_code, description);
}

GLFWWindow::GLFWWindow(const std::string& title, unsigned int width,
                       unsigned height) {
  if (!is_glfw_initialized_) {
    glfwSetErrorCallback(GLFWErrorCallback);
    bool success = glfwInit();
    CORE_ASSERT(success, "Failed to initialized glfw.");
    is_glfw_initialized_ = success;
  }

  window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  data_.is_vsync = false;
  glfwMakeContextCurrent(window_);
  int glad_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  CORE_ASSERT(glad_status, "Failed to Initailized GLAD");
  glfwSetWindowUserPointer(window_,
                           &data_);  // set user poing so that we can get data_
                                     // in event handle function

  glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
    WindowCloseEvent event;
    WindowData data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });

  glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int x, int y) {
    WindowResizeEvent event(x, y);
    WindowData data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });

  glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x, double y) {
    MouseMovedEvent event(x, y);
    WindowData data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });

  glfwSetMouseButtonCallback(
      window_, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData data =
            *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (!data.event_listener_) {
          CORE_LOG_WARN("event callback function has not been set yet.");
        }
        if (action == GLFW_PRESS) {
          MouseButtonPressedEvent event(button);
          data.event_listener_(event);  // pass event to Application's method
        } else if (action == GLFW_RELEASE) {
          MouseButtonReleasedEvent event(button);
          data.event_listener_(event);  // pass event to Application's method
        }
      });

  glfwSetScrollCallback(
      window_, [](GLFWwindow* window, double offset_x, double offset_y) {
        MouseScrolledEvent event(offset_x, offset_y);
        WindowData data =
            *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (!data.event_listener_) {
          CORE_LOG_WARN("event callback function has not been set yet.");
        }
        data.event_listener_(event);  // pass event to Application's method
      });

  glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int character) {
    KeyTypedEvent event(character);
    WindowData data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (!data.event_listener_) {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
    data.event_listener_(event);  // pass event to Application's method
  });
}

GLFWWindow::~GLFWWindow() { glfwDestroyWindow(window_); }

void GLFWWindow::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(window_);
}

void* GLFWWindow::GetNativeWindow() { return window_; }

unsigned int GLFWWindow::GetWidth() const {
  int x;
  glfwGetWindowSize(window_, &x, nullptr);
  return x;
}

unsigned int GLFWWindow::GetHeight() const {
  int y;
  glfwGetWindowSize(window_, nullptr, &y);
  return y;
}

void GLFWWindow::SetVSync(bool open) {
  if (open) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  data_.is_vsync = open;
}

bool GLFWWindow::IsVSync() const { return data_.is_vsync; }
}  // namespace Genesis