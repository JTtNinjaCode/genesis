#include "renderer_3d.h"

#include <glad/glad.h>

#include "core/log/log.h"
#include "core/renderer/render_command.h"
#include "core/renderer/shader_library.h"

namespace genesis {
void Renderer3D::Init() {
  CORE_LOG_TRACE("Start to init Renderer3D's Context.");
  ShaderLibrary::Init();
  ShaderLibrary::AddShader("skybox_shader", "./assets/shaders/skybox.vert", "./assets/shaders/skybox.frag");

  // include shader lib.
  CORE_LOG_TRACE("Finish to init Renderer3D's Context.");
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

  // quick and dirty:draw sky box
  auto& skybox_shader_ = ShaderLibrary::GetShader("skybox_shader");
  skybox_shader_.Bind();
  skybox_shader_.SetUniform("u_projection", camera_->GetProjection());
  skybox_shader_.SetUniform("u_view", camera_->GetView());
  auto& skybox = camera_->GetSkybox();
  if (skybox != nullptr) {
    skybox->Bind();
    skybox_shader_.SetUniform("u_skybox", 0);
    auto& vertex_array = skybox->GetVertexArray();
    vertex_array.Bind();
    render_command.DrawArray(vertex_array);
  }
}

void Renderer3D::EndScene() {}

void Renderer3D::Submit(Shader& shader, const VertexArray& vertex_array, const glm::mat4& model_matrix,
                        const Light* light) {
  shader.Bind();
  shader.SetUniform("u_model", model_matrix);

  if (camera_ != nullptr) {
    SetCameraUniform(shader, *camera_);
  }

  if (light != nullptr) {
    SetLightUniform(shader, *light);
  }

  vertex_array.Bind();
  if (vertex_array.HasIndex()) {
    RenderCommand::GetInstance().DrawIndex(vertex_array);
  } else {
    RenderCommand::GetInstance().DrawArray(vertex_array);
  }
}

void Renderer3D::Submit(Shader& shader, const VertexArray& vertex_array, const VertexBuffer& model_matrices,
                        const int instance_count, const Light* light) {}

void Renderer3D::Submit(Shader& shader, const Model& model, const glm::mat4& model_matrix, const Light* light) {
  shader.Bind();
  shader.SetUniform("u_model", model_matrix);

  if (camera_ != nullptr) {
    SetCameraUniform(shader, *camera_);
  }

  if (light != nullptr) {
    SetLightUniform(shader, *light);
  }

  SetModelsUniformsAndDraw(shader, model);
}

void Renderer3D::Submit(Shader& shader, const Model& model, const VertexBuffer& model_matrices,
                        const int instance_count, const Light* light) {
  shader.Bind();

  if (camera_ != nullptr) {
    SetCameraUniform(shader, *camera_);
  }

  if (light != nullptr) {
    SetLightUniform(shader, *light);
  }

  const auto& meshes = model.GetMeshes();
  for (const auto& mesh : meshes) {
    const auto& textures = mesh.GetTextures();
    // TODO:texture dispatch
    unsigned int diffuse_texture_counter = 1;
    unsigned int specular_texture_counter = 1;
    for (int i = 0; i < textures.size(); i++) {
      const auto& texture = textures[i];
      texture->Bind(i);
      switch (texture->GetTextureType()) {
        case TextureType::kDiffuse:
          shader.SetUniform(std::string("material.diffuse") + std::to_string(diffuse_texture_counter++), i);
          break;
        case TextureType::kSpecular:
          shader.SetUniform(std::string("material.specular") + std::to_string(specular_texture_counter++), i);
          break;
        default:
          CORE_ASSERT(false, "invalid texture type.");
      }
    }
    model_matrices.Bind();
    auto& vao = mesh.GetVAO();
    // quick and dirty
    auto vao_id = *(GLuint*)vao.GetId();
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    RenderCommand::GetInstance().DrawIndexInstanced(mesh.GetVAO(), instance_count);
  }
}

void Renderer3D::SetLightUniform(Shader& shader, const Light& light) {
  shader.Bind();
  light.GetUniform()->BindSlot(2);
  shader.SetUniformBlock("u_light", 2);
}

void Renderer3D::SetCameraUniform(Shader& shader, const Camera3DInterface& camera) {
  shader.Bind();
  shader.SetUniform("u_projection", camera.GetProjection());
  shader.SetUniform("u_view", camera.GetView());
  shader.SetUniform("u_camera_position", camera.GetPosition());
  shader.SetUniform("u_camera_far", camera.GetFar());
  shader.SetUniform("u_camera_near", camera.GetNear());
}

void Renderer3D::SetModelsUniformsAndDraw(Shader& shader, const Model& model) {
  const auto& meshes = model.GetMeshes();
  for (const auto& mesh : meshes) {
    const auto& textures = mesh.GetTextures();
    // TODO:texture dispatch
    unsigned int diffuse_texture_counter = 1;
    unsigned int specular_texture_counter = 1;
    for (int i = 0; i < textures.size(); i++) {
      const auto& texture = textures[i];
      texture->Bind(i);
      switch (texture->GetTextureType()) {
        case TextureType::kDiffuse:
          shader.SetUniform(std::string("material.diffuse") + std::to_string(diffuse_texture_counter++), i);
          break;
        case TextureType::kSpecular:
          shader.SetUniform(std::string("material.specular") + std::to_string(specular_texture_counter++), i);
          break;
        default:
          CORE_ASSERT(false, "invalid texture type.");
      }
    }

    RenderCommand::GetInstance().DrawIndex(mesh.GetVAO());
  }
}
}  // namespace genesis
