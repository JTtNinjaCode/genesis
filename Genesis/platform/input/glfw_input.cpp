#include "glfw_input.h"

#include <GLFW/glfw3.h>

#include "core/application.h"
namespace Genesis {
bool GLFWInput::IsKeyPressed(int key) const {
  return (GLFW_PRESS ==
          glfwGetKey(static_cast<GLFWwindow*>(
                         Application::Get().GetWindow().GetNativeWindow()),
                     key));
}

float GLFWInput::GetMouseButton(int button) const {
  return (
      GLFW_PRESS ==
      glfwGetMouseButton(static_cast<GLFWwindow*>(
                             Application::Get().GetWindow().GetNativeWindow()),
                         button));
}

std::pair<float, float> GLFWInput::GetMousePosition() const {
  double xpos, ypos;
  glfwGetCursorPos(static_cast<GLFWwindow*>(
                       Application::Get().GetWindow().GetNativeWindow()),
                   &xpos, &ypos);
  return {xpos, ypos};
}

float GLFWInput::GetMousePositionX() const {
  double xpos;
  glfwGetCursorPos(static_cast<GLFWwindow*>(
                       Application::Get().GetWindow().GetNativeWindow()),
                   &xpos, nullptr);
  return xpos;
}

float GLFWInput::GetMousePositionY() const {
  double ypos;
  glfwGetCursorPos(static_cast<GLFWwindow*>(
                       Application::Get().GetWindow().GetNativeWindow()),
                   nullptr, &ypos);
  return ypos;
}
}  // namespace Genesis
