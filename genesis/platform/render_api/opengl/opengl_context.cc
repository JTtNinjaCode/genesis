#include "opengl_context.h"

#pragma warning(push)
#include <glad/glad.h>
#pragma warning(pop)

#include "core/log/log.h"

namespace genesis {

void APIENTRY DebugOutput(GLenum source, GLenum type, unsigned int id,
                          GLenum severity, GLsizei length, const char* message,
                          const void* userParam);

OpenGLContext::OpenGLContext(GLFWwindow* window) : context_(window) {
  CORE_ASSERT(context_, "Graphic context is null.");
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(context_);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  CORE_ASSERT(status, "Failed to initialize Glad.");
  CORE_LOG_TRACE("OpenGL Version¡G{0}.{1}", GLVersion.major, GLVersion.minor);

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

  glDebugMessageCallback(DebugOutput, nullptr);
  CORE_LOG_TRACE("OpenGL Debug Mode¡G{0}", "Enable");
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(context_); }

void APIENTRY DebugOutput(GLenum source, GLenum type, unsigned int id,
                          GLenum severity, GLsizei length, const char* message,
                          const void* userParam) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  CORE_LOG_TRACE("Debug message ({0}):", message);

  switch (source) {
    case GL_DEBUG_SOURCE_API:
      CORE_LOG_TRACE("Source: API");
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      CORE_LOG_TRACE("Source: Window System");
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      CORE_LOG_TRACE("Source: Shader Compiler");
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      CORE_LOG_TRACE("Source: Third Party");
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      CORE_LOG_TRACE("Source: Application");
      break;
    case GL_DEBUG_SOURCE_OTHER:
      CORE_LOG_TRACE("Source: Other");
      break;
  }

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      CORE_LOG_TRACE("Type: Error");
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      CORE_LOG_TRACE("Type: Deprecated Behaviour");
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      CORE_LOG_TRACE("Type: Undefined Behaviour");
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      CORE_LOG_TRACE("Type: Portability");
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      CORE_LOG_TRACE("Type: Performance");
      break;
    case GL_DEBUG_TYPE_MARKER:
      CORE_LOG_TRACE("Type: Marker");
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      CORE_LOG_TRACE("Type: Push Group");
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      CORE_LOG_TRACE("Type: Pop Group");
      break;
    case GL_DEBUG_TYPE_OTHER:
      CORE_LOG_TRACE("Type: Other");
      break;
  }

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      CORE_LOG_TRACE("Severity: high");
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      CORE_LOG_TRACE("Severity: medium");
      break;
    case GL_DEBUG_SEVERITY_LOW:
      CORE_LOG_TRACE("Severity: low");
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      CORE_LOG_TRACE("Severity: notification");
      break;
  }
  CORE_ASSERT(false, "Opengl Error!");
}

}  // namespace genesis