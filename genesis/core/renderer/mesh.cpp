#include "mesh.h"

#include "core/log/log.h"
#include "core/renderer/render_command.h"
namespace genesis {
void Mesh::Draw(Shader& shader) const {
  unsigned int diffuse_texture_counter = 1;
  unsigned int specular_texture_counter = 1;
  for (int i = 0; i < textures_.size(); i++) {
    const auto& texture = textures_[i];
    texture->Bind(i);
    switch (texture->GetTextureType()) {
      case TextureType::Diffuse:
        shader.SetUniform(std::string("material.diffuse") + std::to_string(diffuse_texture_counter++), i);
        break;
      case TextureType::Specular:
        shader.SetUniform(std::string("material.specular") + std::to_string(specular_texture_counter++), i);
        break;
      default:
        CORE_ASSERT(false, "invalid texture type.");
    }
  }
  vao_->Bind();
  RenderCommand::GetInstance().DrawIndexed(*vao_);
}

void Mesh::DrawInstanced(Shader& shader, unsigned int count) const {
  // TODO: drawInstaced

  // unsigned int diffuseTextureCounter = 1;
  // unsigned int specularTextureCounter = 1;
  // for (unsigned int i = 0; i < textures_.size(); i++) {
  //   const auto& texture = textures_[i];
  //   texture->Bind(i);
  //   switch (texture.getTextureType()) {
  //     case TextureType::Diffuse:
  //       shader.setUniform(std::string("material.diffuse") +
  //                             std::to_string(diffuseTextureCounter++),
  //                         i);
  //       break;
  //     case TextureType::Specular:
  //       shader.setUniform(std::string("material.diffuse") +
  //                             std::to_string(specularTextureCounter++),
  //                         i);
  //       break;
  //   }
  // }
  // vbo_->Bind();
  // vao_->Bind();
  // ebo_->Bind();
  // glDrawElementsInstanced(GL_TRIANGLES, ebo_->GetCount(), GL_UNSIGNED_INT, 0,
  //                         count);
}

}  // namespace genesis