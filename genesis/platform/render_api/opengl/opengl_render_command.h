#pragma once
#include "core/renderer/render_command.h"
namespace genesis {
class OpenGLRenderCommand : public RenderCommand {
 public:
  void SetClearColor(glm::vec4 color) override;
  void Clear() override;
  void DrawIndexed(const VertexArray& vertex_array) override;
};
}  // namespace genesis
