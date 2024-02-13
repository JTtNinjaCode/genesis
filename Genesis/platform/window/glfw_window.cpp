#include "glfw_window.h"

#include "core/log.h"
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
  glfwSetWindowUserPointer(window_,
                           &data_);  // set user poing so that we can get data_
                                     // in event handle function

  glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
    WindowCloseEvent event;
    WindowData data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (data.event_listener_) {
      data.event_listener_(event);  // pass event to Application's method
    } else {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
  });

  glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int x, int y) {
    WindowResizeEvent event(x, y);
    WindowData data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    if (data.event_listener_) {
      data.event_listener_(event);  // pass event to Application's method
    } else {
      CORE_LOG_WARN("event callback function has not been set yet.");
    }
  });
}

GLFWWindow::~GLFWWindow() { glfwDestroyWindow(window_); }

void GLFWWindow::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(window_);
}

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