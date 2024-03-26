#include "renderer_2d.h"

#include <glad/glad.h>

#include "core/log.h"
#include "core/renderer/render_command.h"
#include "platform/render_api/opengl/opengl_shader.h"
namespace genesis {
Renderer2D::Renderer2D() { RenderCommand::GetInstanced()->SetBlend(true); }
void Renderer2D::BeginScene(const OrthographicCamera2D& camera) { camera_ = &camera; }
void Renderer2D::EndScene() {}
void Renderer2D::Submit(Shader& shader, const VertexArray& vertex_array,
                        const glm::mat4& model_matrix) {
  vertex_array.Bind();
  shader.Bind();
  OpenGLShader& opengl_shader = dynamic_cast<OpenGLShader&>(shader);
  opengl_shader.SetUniform("u_view_projection",
                           camera_->GetProjection() * camera_->GetView());
  opengl_shader.SetUniform("u_model", model_matrix);

  RenderCommand::GetInstanced()->DrawIndexed(vertex_array);
}
}  // namespace genesis
