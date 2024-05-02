#pragma once
#include <iostream>
#include <vector>

#include "core/component/component.h"
#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/texture.h"
#include "core/renderer/vertex_array.h"

namespace genesis {
class Mesh {
 public:
  Mesh(std::shared_ptr<VertexArray>& vao, std::vector<std::shared_ptr<Texture2D>>&& textures)
      : vao_(std::move(vao)), textures_(std::move(textures)) {}

  void Draw(Shader& shader) const;
  void DrawInstanced(Shader& shader, unsigned int count) const;

 private:
  std::shared_ptr<VertexArray> vao_;
  std::vector<std::shared_ptr<Texture2D>> textures_;
};
}  // namespace genesis