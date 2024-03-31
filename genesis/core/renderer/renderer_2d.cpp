#include "renderer_2d.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include "core/log/log.h"
#include "core/renderer/render_command.h"
#include "core/renderer/shader_library.h"

namespace genesis {
Renderer2D::Renderer2D() {
  RenderCommand::GetInstanced().SetBlend(true);
  RenderCommand::GetInstanced().SetDepthTest(true);
  std::array<float, 20> data{-0.5, -0.5, 0.0, 0.0,  0.0, 0.5, -0.5,
                             0.0,  1.0,  0.0, -0.5, 0.5, 0.0, 0.0,
                             1.0,  0.5,  0.5, 0.0,  1.0, 1.0};
  quad_vbo_ = genesis::VertexBuffer::Create(data.data(), sizeof(data));
  quad_vbo_->Bind();

  unsigned int elements[6] = {0, 1, 2, 1, 2, 3};
  quad_ebo_ = genesis::IndexBuffer::Create(elements, sizeof(elements));
  quad_ebo_->Bind();

  genesis::BufferLayout buffer_layout{
      {genesis::MathDataType::kFloat3, genesis::MathDataType::kFloat2}};
  quad_vao_ = genesis::VertexArray::Create(buffer_layout);
  quad_vao_->AddVertexBuffer(*quad_vbo_);
  quad_vao_->SetIndexBuffer(*quad_ebo_);

  auto& shader_library = genesis::ShaderLibrary::GetInstance();
  shader_library.AddShader("texture_2d", "./assets/shaders/texture_2d.vert",
                           "./assets/shaders/texture_2d.frag");

  unsigned char white_picture_data[4] = {0xff, 0xff, 0xff, 0xff};
  white_texture_ = Texture2D::Create(white_picture_data, 4, 1, 1);
}

void Renderer2D::BeginScene(const OrthographicCamera2D& camera) {
  camera_ = &camera;

  auto& shader_library = genesis::ShaderLibrary::GetInstance();
  auto& flat_shader = shader_library.GetShader("texture_2d");
  flat_shader.Bind();
  flat_shader.SetUniform("u_view_projection",
                         camera_->GetProjection() * camera_->GetView());

  auto& texture_shader = shader_library.GetShader("texture_2d");
  texture_shader.Bind();
  texture_shader.SetUniform("u_view_projection",
                            camera_->GetProjection() * camera_->GetView());
}

void Renderer2D::EndScene() {}

Renderer2D& Renderer2D::GetInstanced() {
  static Renderer2D renderer_2d;
  return renderer_2d;
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
                          float rotate_radians, const glm::vec4& color) {
  auto& shader_library = genesis::ShaderLibrary::GetInstance();
  auto& shader = shader_library.GetShader("texture_2d");
  shader.Bind();

  glm::mat4 model(1.0f);
  model *= glm::translate(model, position);
  model *= glm::scale(glm::identity<glm::mat4>(), {size.x, size.y, 0.0f});
  model *= glm::rotate(glm::identity<glm::mat4>(), rotate_radians, {0, 0, 1});
  shader.SetUniform("u_model", model);
  shader.SetUniform("u_texture", 1);
  shader.SetUniform("u_flat_color", color);

  white_texture_->Bind(1);
  quad_vao_->Bind();
  RenderCommand::GetInstanced().DrawIndexed(*quad_vao_);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
                          float rotate_radians, const Texture& texture) {
  auto& shader_library = genesis::ShaderLibrary::GetInstance();
  auto& shader = shader_library.GetShader("texture_2d");
  shader.Bind();

  glm::mat4 model(1.0f);
  model *= glm::translate(model, position);
  model *= glm::scale(glm::identity<glm::mat4>(), {size.x, size.y, 1.0f});
  model *= glm::rotate(glm::identity<glm::mat4>(), rotate_radians, {0, 0, 1});
  shader.SetUniform("u_model", model);
  shader.SetUniform("u_texture", 1);
  shader.SetUniform("u_flat_color", {1.0f, 1.0f, 1.0f, 1.0f});

  texture.Bind(1);
  quad_vao_->Bind();
  RenderCommand::GetInstanced().DrawIndexed(*quad_vao_);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
                          float rotate_radians, const Texture& texture,
                          const glm::vec4& color) {
  auto& shader_library = genesis::ShaderLibrary::GetInstance();
  auto& shader = shader_library.GetShader("texture_2d");
  shader.Bind();

  glm::mat4 model(1.0f);
  model *= glm::translate(model, position);
  model *= glm::scale(glm::identity<glm::mat4>(), {size.x, size.y, 1.0f});
  model *= glm::rotate(glm::identity<glm::mat4>(), rotate_radians, {0, 0, 1});
  shader.SetUniform("u_model", model);
  shader.SetUniform("u_texture", 1);
  shader.SetUniform("u_flat_color", color);

  texture.Bind(1);
  quad_vao_->Bind();
  RenderCommand::GetInstanced().DrawIndexed(*quad_vao_);
}
}  // namespace genesis
