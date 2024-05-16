#include "window.h"

#include <memory>

#include "platform/window/glfw_window.h"
namespace genesis {
std::shared_ptr<Window> genesis::Window::Create(std::string title, unsigned int width, unsigned int height) {
  return std::make_shared<GLFWWindow>(title, width, height);
}
}  // namespace genesis