#pragma once
#include "core/renderer/camera/orthographic_camera.h"
#include "core/renderer/shader.h"
#include "core/renderer/texture.h"
#include "core/renderer/vertex_array.h"
namespace genesis {
class Renderer2D {
 public:
  static Renderer2D& GetInstance();
  void BeginScene(const OrthographicCamera2D& camera);
  void EndScene();
  // void Submit(Shader& shader, const VertexArray& vertex_array,
  //             const glm::mat4& model_matrix);

  void DrawQuad(const glm::vec3& position, const glm::vec2& size,
                float rotate_radinas, const glm::vec4& color);
  void DrawQuad(const glm::vec3& position, const glm::vec2& size,
                float rotate_radinas, const Texture& texture);
  void DrawQuad(const glm::vec3& position, const glm::vec2& size,
                float rotate_radinas, const Texture& texture,
                const glm::vec4& color);

 private:
  Renderer2D();

  const OrthographicCamera2D* camera_ = nullptr;

  std::shared_ptr<VertexArray> quad_vao_;
  std::shared_ptr<VertexBuffer> quad_vbo_;
  std::shared_ptr<IndexBuffer> quad_ebo_;
  std::shared_ptr<Texture> white_texture_;
};
}  // namespace genesis
