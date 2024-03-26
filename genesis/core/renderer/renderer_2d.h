#pragma once
#include "core/renderer/camera/orthographic_camera.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertex_array.h"
namespace genesis {
class Renderer2D {
 public:
  Renderer2D();
  void BeginScene(const OrthographicCamera2D& camera);
  void EndScene();
  void Submit(Shader& shader, const VertexArray& vertex_array,
              const glm::mat4& model_matrix);

 private:
  const OrthographicCamera2D* camera_ = nullptr;
};
}  // namespace genesis
