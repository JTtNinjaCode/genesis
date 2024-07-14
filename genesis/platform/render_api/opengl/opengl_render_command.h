#pragma once
#include <glad/glad.h>

#include "core/renderer/render_command.h"
namespace genesis {
class OpenGLRenderCommand : public RenderCommand {
 public:
  void SetClearColor(glm::vec4 color) override;
  void Clear() override;
  void OpenDebugMessage(bool open) override;

  void DrawIndex(const VertexArray& vertex_array) override;
  void DrawIndexInstanced(const VertexArray& vertex_array, const int count) override;
  void DrawArray(const VertexArray& vertex_array) override;
  void DrawArrayInstanced(const VertexArray& vertex_array, const int count) override;

  void SetViewport(int x, int y, int width, int height) override;
  void SetDrawMode(DrawMode mode) override;
  void SetFrontFaceOrder(FacePointOrder face_point_order) override;

  void SetBlendTest(bool enable) override;
  void SetBlendColor(const glm::vec4& color);
  void SetBlendFunc(BlendFactor sfactor, BlendFactor dfactor, CullFace cull_face);
  void SetBlendEquation(BlendEquationMode mode, CullFace cull_face);

  void SetDepthTest(bool enable) override;
  void SetDepthMask(bool enable) override;
  void SetDepthRange(float near_val, float far_val);

  void SetStencilTest(bool enable) override;
  void SetStencilFunc(StencilFunc stencil_fun, int value1, int value2, CullFace cull_face) override;
  void SetStencilMask(bool enable, CullFace cull_face) override;
  void SetStencilOp(bool enable, CullFace cull_face) override;
  void SetBackCullTest(bool enable) override;
  void SetBackCullFace(CullFace cull_face) override;
  void SetPointSize(float size) override;

  void SetTopolgy(Topology topology) override;

 private:
  GLuint topology_type = GL_TRIANGLES;
};
}  // namespace genesis
