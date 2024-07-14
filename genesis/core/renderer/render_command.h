#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "core/renderer/vertex_array.h"
namespace genesis {
enum class DrawMode { kFill, kLine, kPoint };
enum class StencilFunc { kLess, kLessEqual, kEqual, kGreaterEqual, kGreater, kNever, kAlways, kNotEqual };
enum class StencilOp { kKeep, kZero, kReplace, kIncrement, kIncrementWrap, kDecrement, kDecrementWrap, kInvert };
enum class CullFace { kFront, kBack, kFrontAndBack, kKeep };
enum class FacePointOrder { kClockWise, kCounterClockWise };
enum class BlendEquationMode { kAdd, kSubtract, kReverseSubtract, kMin, kMax };
enum class BlendFactor {
  kZero,
  kOne,
  kSrcColor,
  kOneMinusSrcColor,
  kDstColor,
  kOneMinusDstColor,
  kSrcAlpha,
  kOneMinusSrcAlpha,
  kDstAlpha,
  kOneMinusDstAlpha,
  kConstantColor,
  kOneMinusConstantColor,
  kConstantAlpha,
  kOneMinusConstantAlpha
};
enum class Topology { kPoint, kLines, kLineStrip, kTriangle, kTrangleStrip };

class RenderCommand {
 public:
  static RenderCommand& GetInstance();

  virtual void SetClearColor(glm::vec4 color) = 0;
  virtual void Clear() = 0;

  virtual void DrawIndex(const VertexArray& vertex_array) = 0;
  virtual void DrawIndexInstanced(const VertexArray& vertex_array, const int count) = 0;
  virtual void DrawArray(const VertexArray& vertex_array) = 0;
  virtual void DrawArrayInstanced(const VertexArray& vertex_array, const int count) = 0;

  virtual void SetViewport(int x, int y, int width, int height) = 0;
  virtual void SetDrawMode(DrawMode enable) = 0;
  virtual void SetFrontFaceOrder(FacePointOrder face_point_order) = 0;

  virtual void SetBlendTest(bool enable) = 0;
  virtual void SetBlendColor(const glm::vec4& color) = 0;  // glBlendColor
  virtual void SetBlendFunc(BlendFactor sfactor, BlendFactor dfactor,
                            CullFace cull_face = CullFace::kKeep) = 0;  // glBlendFuncSeparate
  virtual void SetBlendEquation(BlendEquationMode mode,
                                CullFace cull_face = CullFace::kKeep) = 0;  // glBlendFuncSeparate

  virtual void SetDepthTest(bool enable) = 0;
  virtual void SetDepthMask(bool enable) = 0;
  virtual void SetDepthRange(float near_val, float far_val) = 0;

  virtual void SetStencilTest(bool enable) = 0;
  virtual void SetStencilFunc(StencilFunc stencil_func, int ref, int mask, CullFace cull_face = CullFace::kKeep) = 0;
  virtual void SetStencilMask(bool enable, CullFace cull_face = CullFace::kKeep) = 0;
  virtual void SetStencilOp(bool enable, CullFace cull_face = CullFace::kKeep) = 0;

  virtual void SetBackCullTest(bool enable) = 0;
  virtual void SetBackCullFace(CullFace cull_face) = 0;
  virtual void SetPointSize(float size) = 0;

  virtual void SetTopolgy(Topology topology) = 0;

 private:
  static std::unique_ptr<RenderCommand> render_command_;
};
}  // namespace genesis
