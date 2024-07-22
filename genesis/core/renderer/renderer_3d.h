#pragma once
#include <memory>

#include "core/component/light.h"
#include "core/renderer/camera/camera.h"
#include "core/renderer/grid.h"
#include "core/renderer/model.h"
#include "core/renderer/renderer_api.h"
#include "core/renderer/shader.h"
#include "core/renderer/vertex_array.h"
namespace genesis {
class Renderer3D {
 public:
  static void Init();
  static void Uninit();
  Renderer3D();
  void BeginScene(const Camera3DInterface& camera);
  void EndScene();
  // draw vao
  void Submit(Shader& shader, const VertexArray& vertex_array, const glm::mat4& model_matrix, const Light* light);
  // draw vao instances(assume ssbo store model matrix's data)
  void Submit(Shader& shader, const VertexArray& vertex_array, const VertexBuffer& model_matrices,
              const int instance_count, const Light* light = nullptr);
  // draw model
  void Submit(Shader& shader, const Model& model, const glm::mat4& model_matrix = {1.0f}, const Light* light = nullptr);
  // draw model instances(assume ssbo store model matrix's data)
  void Submit(Shader& shader, const Model& model, const VertexBuffer& model_matrices, const int instance_count,
              const Light* light = nullptr);

 private:
  void SetLightUniform(Shader& shader, const Light& light);
  void SetCameraUniform(Shader& shader, const Camera3DInterface& camera);
  void SetModelsUniformsAndDraw(Shader& shader, const Model& model);
  const Camera3DInterface* camera_ = nullptr;
};
}  // namespace genesis
