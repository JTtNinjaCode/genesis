#include "platform/window/glfw_window.h"

#pragma warning(push)
#pragma warning(disable : 4005)
#include <glad/glad.h>
#pragma warning(pop)

#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/events/window_event.h"
#include "core/log.h"
#include "core/renderer/graphic_context.h"
#include "platform/render_api/opengl/opengl_context.h"

namespace genesis {
bool GLFWWindow::is_glfw_initialized_ = false;

static void GLFWErrorCallback(int error_code, const char* description) {
  CORE_LOG_WARN("glfw Error:[{0}], {1}", error_code, description);
}

GLFWWindow::GLFWWindow(const std::string& title, unsigned int width,
                       unsigned height) {
  if (!is_glfw_initialized_) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(GLFWErrorCallback);
    bool success = glfwInit();
    CORE_ASSERT(success, "Failed to initialized glfw.");
    is_glfw_initialized_ = true;
  }

  window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  context_ = new OpenGLContext(window_); // window_ contain opengl context
  context_->Init();

  SetVSync(false);
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
  context_->SwapBuffers();
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
  data_.is_vsync_ = open;
}

bool GLFWWindow::IsVSync() const { return data_.is_vsync_; }
}  // namespace genesis