#include "renderer_3d.h"

#include <glad/glad.h>

#include "core/log/log.h"
#include "core/renderer/render_command.h"

namespace genesis {
std::shared_ptr<Shader> Renderer3D::skybox_shader_;

void Renderer3D::Init() {
  CORE_LOG_TRACE("Start to init Renderer3D's Context");
  skybox_shader_ = Shader::Create("./assets/shaders/skybox.vert", "./assets/shaders/skybox.frag");
  CORE_LOG_TRACE("Finish to init Renderer3D's Context");
}
void Renderer3D::Uninit() {}
Renderer3D::Renderer3D() {
  RenderCommand::GetInstance().SetBlendTest(true);
  RenderCommand::GetInstance().SetDepthTest(true);
}
void Renderer3D::BeginScene(const Camera3DInterface& camera) {
  camera_ = &camera;
  RenderCommand& render_command = RenderCommand::GetInstance();
  render_command.SetClearColor(camera_->GetClearColor());
  render_command.Clear();

  skybox_shader_->Bind();
  skybox_shader_->SetUniform("u_projection", camera_->GetProjection());
  skybox_shader_->SetUniform("u_view", camera_->GetView());
  auto& skybox = camera_->GetSkybox();
  if (skybox != nullptr) {
    skybox->Bind();
    skybox_shader_->SetUniform("u_skybox", 0);
    auto& vertex_array = skybox->GetVertexArray();
    vertex_array.Bind();
    render_command.DrawArray(vertex_array);
  }
}
void Renderer3D::EndScene() {}
void Renderer3D::Submit(Shader& shader, const VertexArray& vertex_array, const glm::mat4& model_matrix,
                        const Light* light, const CameraData* camera) {
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
  RenderCommand::GetInstance().DrawIndex(vertex_array);
}
void Renderer3D::Submit(Shader& shader, const Model& model, const glm::mat4& model_matrix, const Light* light,
                        const CameraData* camera) {
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
    auto& skybox = camera_->GetSkybox();
    if (skybox != nullptr) {
      shader.SetUniform("u_skybox", *reinterpret_cast<int*>(skybox->GetTextureID()));
    }
  }
  model.Draw(shader);
}
}  // namespace genesis
