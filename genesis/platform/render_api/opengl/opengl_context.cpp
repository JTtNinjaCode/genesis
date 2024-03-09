#include "opengl_context.h"

#pragma warning(push)
#include <glad/glad.h>
#pragma warning(pop)

#include "core/log.h"

namespace genesis {
OpenGLContext::OpenGLContext(GLFWwindow* window) : context_(window) {
  CORE_ASSERT(context_, "Graphic context is null.");
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(context_);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  CORE_ASSERT(status, "Failed to initialize Glad.");
  CORE_LOG_TRACE("OpenGL Version¡G{0}.{1}\n", GLVersion.major, GLVersion.minor);
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(context_); }

}  // namespace genesis