#pragma once
#include <memory>

#include "core/renderer/camera/perspective_camera.h"
#include "core/renderer/model.h"
#include "core/renderer/renderer_api.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertex_array.h"

namespace genesis {
class Renderer3D {
 public:
  Renderer3D();
  void BeginScene(const PerspectiveCamera& camera);
  void EndScene();
  void Submit(Shader& shader, const VertexArray& vertex_array, const glm::mat4& model_matrix);
  void Submit(Shader& shader, Model& model, const glm::mat4& model_matrix);

 private:
  const PerspectiveCamera* camera_ = nullptr;
};
}  // namespace genesis
