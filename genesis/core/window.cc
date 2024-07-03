#include "window.h"

#include "platform/window/glfw_window.h"
namespace genesis {
std::shared_ptr<Window> Window::Create(const std::string &title, unsigned int width, unsigned int height) {
  return std::make_shared<GLFWWindow>(title, width, height);
}
}  // namespace genesis