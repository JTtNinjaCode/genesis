#include "Renderer.h"

#include <glad/glad.h>

#include "core/log.h"
#include "core/renderer/render_command.h"
namespace genesis {
void Renderer::BeginScene(PerspectiveCamera& camera) { camera_ = &camera; }
void Renderer::EndScene() {}
void Renderer::Submit(Shader& shader, const VertexArray& vertex_array) {
  vertex_array.Bind();
  shader.Bind();
  shader.SetUniform("u_view_projection",
                    camera_->GetProjection() * camera_->GetView());

  RenderCommand::GetInstanced()->DrawIndexed(vertex_array);
}
}  // namespace genesis
