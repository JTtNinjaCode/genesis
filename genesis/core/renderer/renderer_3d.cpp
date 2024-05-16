#include "renderer_3d.h"

#include <glad/glad.h>

#include "core/log/log.h"
#include "core/renderer/render_command.h"

namespace genesis {
Renderer3D::Renderer3D() {
  RenderCommand::GetInstance().SetBlend(true);
  RenderCommand::GetInstance().SetDepthTest(true);
}
void Renderer3D::BeginScene(const PerspectiveCamera& camera) {
  camera_ = &camera;
  RenderCommand& render_command = RenderCommand::GetInstance();
  render_command.SetClearColor(camera_->GetClearColor());
  render_command.Clear();
}
void Renderer3D::EndScene() {}
void Renderer3D::Submit(Shader& shader, const VertexArray& vertex_array, const glm::mat4& model_matrix,
                        const Light* light, const PerspectiveCamera* camera) {
  vertex_array.Bind();
  shader.Bind();
  shader.SetUniform("u_projection", camera_->GetProjection());
  shader.SetUniform("u_view", camera_->GetView());
  shader.SetUniform("u_model", model_matrix);
  shader.SetUniform("u_camera_position", camera->GetPosition());
  shader.SetUniform("u_camera_far", camera->GetFar());
  shader.SetUniform("u_camera_near", camera->GetNear());

  // set light uniform
  if (light != nullptr) {
    light->GetUniform()->BindSlot(2);
    shader.SetUniformBlock("u_light", 2);
  }
  RenderCommand::GetInstance().DrawIndexed(vertex_array);
}
void Renderer3D::Submit(Shader& shader, const Model& model, const glm::mat4& model_matrix, const Light* light,
                        const PerspectiveCamera* camera) {
  shader.Bind();
  glm::mat4 projection_view = camera_->GetProjection() * camera_->GetView();
  shader.SetUniform("u_projection", camera_->GetProjection());
  shader.SetUniform("u_view", camera_->GetView());
  shader.SetUniform("u_model", model_matrix);
  // set light uniform
  if (light != nullptr) {
    light->GetUniform()->BindSlot(2);
    shader.SetUniformBlock("u_light", 2);
  }
  // set camera uniform
  if (camera != nullptr) {
    shader.SetUniform("u_camera_position", camera->GetPosition());
  }
  model.Draw(shader);
}
}  // namespace genesis
