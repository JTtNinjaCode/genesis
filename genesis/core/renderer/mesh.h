#pragma once
#include <iostream>
#include <vector>

#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/texture.h"
#include "core/renderer/vertex_array.h"

namespace genesis {
class Mesh {
 public:
  Mesh(std::shared_ptr<VertexBuffer>& vbo, std::shared_ptr<VertexArray>& vao,
       std::shared_ptr<IndexBuffer>& ebo,
       std::vector<std::shared_ptr<Texture2D>>&& textures)
      : vbo_(std::move(vbo)),
        vao_(std::move(vao)),
        ebo_(std::move(ebo)),
        textures_(std::move(textures)) {}

  void Draw(Shader& shader);
  void DrawInstanced(Shader& shader, unsigned int count);

 private:
  std::shared_ptr<VertexBuffer> vbo_;
  std::shared_ptr<VertexArray> vao_;
  std::shared_ptr<IndexBuffer> ebo_;
  std::vector<std::shared_ptr<Texture2D>> textures_;
};
}  // namespace genesis