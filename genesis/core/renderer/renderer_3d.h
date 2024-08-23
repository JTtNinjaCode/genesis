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
  static void BeginScene(const Camera3DInterface& camera);
  static void EndScene();
  // draw vao
  static void Submit(Shader& shader, const VertexArray& vertex_array, const glm::mat4& model_matrix,
                     const Light* light);
  // draw vao instances(assume ssbo store model matrix's data)
  static void Submit(Shader& shader, const VertexArray& vertex_array, const VertexBuffer& model_matrices,
                     const int instance_count, const Light* light = nullptr);
  // draw model
  static void Submit(Shader& shader, const Model& model, const glm::mat4& model_matrix = {1.0f},
                     const Light* light = nullptr);
  // draw model instances(assume ssbo store model matrix's data)
  static void Submit(Shader& shader, const Model& model, const VertexBuffer& model_matrices, const int instance_count,
                     const Light* light = nullptr);

 private:
  static void SetLightUniform(Shader& shader, const Light& light);
  static void SetCameraUniform(Shader& shader, const Camera3DInterface& camera);
  static void SetModelsUniformsAndDraw(Shader& shader, const Model& model);
  static const Camera3DInterface* camera_;
};
}  // namespace genesis
