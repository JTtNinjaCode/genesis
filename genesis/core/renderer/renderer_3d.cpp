#include "renderer_3d.h"

#include <glad/glad.h>

#include "core/log/log.h"
#include "core/renderer/render_command.h"

namespace genesis {
Renderer3D::Renderer3D() {
  RenderCommand::GetInstanced().SetBlend(true);
  RenderCommand::GetInstanced().SetDepthTest(true);
}
void Renderer3D::BeginScene(const PerspectiveCamera& camera) { camera_ = &camera; }
void Renderer3D::EndScene() {}
void Renderer3D::Submit(Shader& shader, const VertexArray& vertex_array, const glm::mat4& model_matrix) {
  vertex_array.Bind();
  shader.Bind();
  shader.SetUniform("u_view_projection", camera_->GetProjection() * camera_->GetView());
  shader.SetUniform("u_model", model_matrix);

  RenderCommand::GetInstanced().DrawIndexed(vertex_array);
}
void Renderer3D::Submit(Shader& shader, const Model& model, const glm::mat4& model_matrix) {
  shader.Bind();
  shader.SetUniform("u_view_projection", camera_->GetProjection() * camera_->GetView());
  shader.SetUniform("u_model", model_matrix);
  model.Draw(shader);
}
}  // namespace genesis
