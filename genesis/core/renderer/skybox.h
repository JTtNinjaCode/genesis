#pragma once
#include <filesystem>
#include <memory>
#include <vector>

#include "core/renderer/buffer.h"
#include "core/renderer/shader.h"
#include "core/renderer/texture.h"
#include "core/renderer/vertex_array.h"
namespace genesis {
class Skybox {
 public:
  static void Init();
  Skybox(const std::vector<std::filesystem::path>& faces_path);
  void* GetTextureID() const;
  const VertexArray& GetVertexArray() const;
  void Bind() const;

 private:
  static std::shared_ptr<VertexBuffer> vbo_;
  static std::shared_ptr<VertexArray> vao_;
  static std::shared_ptr<IndexBuffer> ibo_;
  static std::shared_ptr<Shader> shader_;

  std::shared_ptr<Texture3D> texture_;
};
}  // namespace genesis