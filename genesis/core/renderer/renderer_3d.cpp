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
  glm::mat4 projection_view = camera_->GetProjection() * camera_->GetView();
  shader.SetUniform("u_view_projection", projection_view);
  shader.SetUniform("u_model", model_matrix);
  // set light uniform
  if (light != nullptr) {
    SetLightUniform(shader, *light);
  }
  // set camera uniform
  if (camera != nullptr) {
    shader.SetUniform("camera_position", camera->GetPosition());
  }
  RenderCommand::GetInstance().DrawIndexed(vertex_array);
}
void Renderer3D::Submit(Shader& shader, const Model& model, const glm::mat4& model_matrix, const Light* light,
                        const PerspectiveCamera* camera) {
  shader.Bind();
  glm::mat4 projection_view = camera_->GetProjection() * camera_->GetView();
  shader.SetUniform("u_view_projection", projection_view);
  shader.SetUniform("u_model", model_matrix);
  // set light uniform
  if (light != nullptr) {
    SetLightUniform(shader, *light);
  }
  // set camera uniform
  if (camera != nullptr) {
    shader.SetUniform("camera_position", camera->GetPosition());
  }
  model.Draw(shader);
}
void Renderer3D::SetLightUniform(Shader& shader, const Light& light) {
  auto color = light.GetColor();
  auto position = light.GetPosition();
  auto direction = light.GetDirection();
  auto constant = light.GetConstant();
  auto linear = light.GetLinear();
  auto quadratic = light.GetQuadratic();
  auto type = light.GetLightType();
  switch (type) {
    case LightType::Directional:
      shader.SetUniform("directional_light.direction", direction);
      shader.SetUniform("directional_light.color", color);
      break;
    case LightType::Point:
      shader.SetUniform("point_light.position", position);
      shader.SetUniform("point_light.constant", constant);
      shader.SetUniform("point_light.linear", linear);
      shader.SetUniform("point_light.quadratic", quadratic);
      shader.SetUniform("point_light.color", color);
      break;
    case LightType::Spot:
      shader.SetUniform("spot_light.position", position);
      shader.SetUniform("spot_light.direction", direction);
      shader.SetUniform("spot_light.constant", constant);
      shader.SetUniform("spot_light.linear", linear);
      shader.SetUniform("spot_light.quadratic", quadratic);
      shader.SetUniform("spot_light.color", color);
      break;
    default:
      CORE_ASSERT(false, "Unknown LightType.");
      break;
  }
}
}  // namespace genesis
