#include "opengl_render_command.h"

#include <glad/glad.h>
namespace genesis {
void OpenGLRenderCommand::SetClearColor(glm::vec4 color) {
  glClearColor(color.x, color.y, color.z, color.w);
}
void OpenGLRenderCommand::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRenderCommand::DrawIndexed(const VertexArray& vertex_array) {
  glDrawElements(GL_TRIANGLES, vertex_array.GetCount(), GL_UNSIGNED_INT,
                 nullptr);
}
void OpenGLRenderCommand::SetBlend(bool enable) {
  if (enable) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  } else {
    glDisable(GL_BLEND);
  }
}
}  // namespace genesis
