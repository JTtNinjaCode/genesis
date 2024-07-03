#include "glfw_context.h"

#include <GLFW/glfw3.h>
#include <core/log/log.h>
namespace genesis {
static void GLFWErrorCallback(int error_code, const char* description) {
  CORE_LOG_WARN("GLFW Error:[{0}], {1}", error_code, description);
}
void GLFWContext::Init() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwSetErrorCallback(GLFWErrorCallback);

  if (bool success = GLFW_TRUE == glfwInit()) {
    CORE_ASSERT(success, "Failed to initialized GLFW.");
  }
}

void GLFWContext::Uninit() { glfwTerminate(); }
}  // namespace genesis