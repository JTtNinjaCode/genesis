#pragma once
#include "core/renderer/render_command.h"
namespace genesis {
class OpenGLRenderCommand : public RenderCommand {
 public:
  void SetClearColor(glm::vec4 color) override;
  void Clear() override;
  void DrawIndexed(const VertexArray& vertex_array) override;
  void SetBlend(bool enable) override;
  void SetViewport(int x, int y, int width, int height) override;
  void SetDepthTest(bool enable) override;
  void SetDrawMode(DrawMode mode) override;
  void SetBackCulling(bool enable) override;
};
}  // namespace genesis
