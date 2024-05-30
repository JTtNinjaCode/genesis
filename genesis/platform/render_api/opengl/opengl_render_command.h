#pragma once
#include "core/renderer/render_command.h"
namespace genesis {
class OpenGLRenderCommand : public RenderCommand {
 public:
  void SetClearColor(glm::vec4 color) override;
  void Clear() override;
  void DrawIndexed(const VertexArray& vertex_array) override;
  void DrawArray(const VertexArray& vertex_array) override;
  void SetBlend(bool enable) override;
  void SetViewport(int x, int y, int width, int height) override;
  void SetDepthTest(bool enable) override;
  void SetDrawMode(DrawMode mode) override;
  void SetPointSize(float size) override;

  void SetFrontFaceOrder(FacePointOrder face_point_order) override;
  void SetDepthMask(bool enable) override;
  void SetStencilTest(bool enable) override;
  void SetStencilFunc(StencilFunc stencil_fun, int value1, int value2, CullFace cull_face) override;
  void SetStencilMask(bool enable, CullFace cull_face) override;
  void SetStencilOp(bool enable, CullFace cull_face) override;
  void SetBackCullTest(bool enable) override;
  void SetBackCullFace(CullFace cull_face) override;
};
}  // namespace genesis
