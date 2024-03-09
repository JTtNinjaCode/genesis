#pragma once
#pragma warning(push)
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include "core/renderer/graphic_context.h"
namespace genesis {

class OpenGLContext : public GraphicContext {
 public:
  OpenGLContext(GLFWwindow* window);
  void Init() override;
  void SwapBuffers() override;

 private:
  GLFWwindow* context_;
};

}  // namespace genesis