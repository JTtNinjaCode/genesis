#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "core/renderer/vertex_array.h"
namespace genesis {
class RenderCommand {
 public:
  static std::shared_ptr<RenderCommand> GetInstanced();

  virtual void SetClearColor(glm::vec4 color) = 0;
  virtual void Clear() = 0;
  virtual void DrawIndexed(const VertexArray& vertex_array) = 0;
  virtual void SetBlend(bool enable) = 0;

 private:
  static std::shared_ptr<RenderCommand> render_command_;
};
}  // namespace genesis
