#include "Renderer.h"

#include <glad/glad.h>

#include "core/log.h"
#include "core/renderer/render_command.h"
namespace genesis {
void Renderer::BeginScene() {}
void Renderer::EndScene() {}
void Renderer::Submit(const VertexArray& vertex_array) {
  vertex_array.Bind();
  RenderCommand::GetInstanced()->DrawIndexed(vertex_array);
}
}  // namespace genesis
