#pragma once
#include <memory>

#include "core/component/light.h"
#include "core/renderer/camera/perspective_camera.h"
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
  void Submit(Shader& shader, const VertexArray& vertex_array, const glm::mat4& model_matrix = {1.0f},
              const Light* light = nullptr, const PerspectiveCamera* camera = nullptr);
  void Submit(Shader& shader, const Model& model, const glm::mat4& model_matrix = {1.0f}, const Light* light = nullptr,
              const PerspectiveCamera* camera = nullptr);

 private:
  const Camera3DInterface* camera_ = nullptr;
  static std::shared_ptr<Shader> skybox_shader_;
};
}  // namespace genesis
