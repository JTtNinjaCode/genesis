#pragma once
#include "core/window.h"
#include "platform/window/glfw_window.h"
namespace Genesis {
class WindowFactory {
 public:
  static std::unique_ptr<Window> Create(const std::string& title, int width,
                                        int height) {
    return std::make_unique<GLFWWindow>(title, width, height);
  }
};
}  // namespace Genesis
