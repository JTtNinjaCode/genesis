#include "opengl_render_command.h"

#include <glad/glad.h>

#include "core/log/log.h"
namespace genesis {
void OpenGLRenderCommand::SetClearColor(glm::vec4 color) { glClearColor(color.x, color.y, color.z, color.w); }

void OpenGLRenderCommand::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void OpenGLRenderCommand::DrawIndex(const VertexArray& vertex_array) {
  glDrawElements(topology_type, vertex_array.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderCommand::DrawIndexInstanced(const VertexArray& vertex_array, const int count) {
  glDrawElementsInstanced(topology_type, vertex_array.GetIndexCount(), GL_UNSIGNED_INT, nullptr, count);
}

void OpenGLRenderCommand::DrawArray(const VertexArray& vertex_array) {
  glDrawArrays(topology_type, 0, vertex_array.GetVertexCount());
}

void OpenGLRenderCommand::DrawArrayInstanced(const VertexArray& vertex_array, const int count) {
  glDrawArraysInstanced(topology_type, 0, vertex_array.GetVertexCount(), count);
}

void OpenGLRenderCommand::SetBlendTest(bool enable) {
  if (enable) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  } else {
    glDisable(GL_BLEND);
  }
}

void OpenGLRenderCommand::SetViewport(int x, int y, int width, int height) { glViewport(x, y, width, height); }

void OpenGLRenderCommand::SetDepthTest(bool enable) {
  glDepthFunc(GL_LEQUAL);
  if (enable) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}

void OpenGLRenderCommand::SetDrawMode(DrawMode mode) {
  if (mode == DrawMode::kLine) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else if (mode == DrawMode::kFill) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  } else if (mode == DrawMode::kPoint) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  }
}

void OpenGLRenderCommand::SetPointSize(float size) { glPointSize(size); }

void OpenGLRenderCommand::SetFrontFaceOrder(FacePointOrder face_point_order) {
  if (face_point_order == FacePointOrder::kClockWise) {
    glFrontFace(GL_CW);
  } else if (face_point_order == FacePointOrder::kCounterClockWise) {
    glFrontFace(GL_CCW);
  }
}

void OpenGLRenderCommand::SetDepthMask(bool enable) {
  if (enable) {
    glDepthMask(0xff);
  } else {
    glDepthMask(0x00);
  }
}

void OpenGLRenderCommand::SetStencilTest(bool enable) {
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  if (enable) {
    glEnable(GL_STENCIL_TEST);
  } else {
    glDisable(GL_STENCIL_TEST);
  }
}

void OpenGLRenderCommand::SetStencilFunc(StencilFunc stencil_func, int ref, int mask, CullFace cull_face) {
  GLenum func{};
  switch (stencil_func) {
    case StencilFunc::kAlways:
      func = GL_ALWAYS;
      break;
    case StencilFunc::kEqual:
      func = GL_EQUAL;
      break;
    case StencilFunc::kGreater:
      func = GL_GREATER;
      break;
    case StencilFunc::kGreaterEqual:
      func = GL_GEQUAL;
      break;
    case StencilFunc::kLessEqual:
      func = GL_LEQUAL;
      break;
    case StencilFunc::kNever:
      func = GL_NEVER;
      break;
    case StencilFunc::kNotEqual:
      func = GL_NOTEQUAL;
      break;
  }
  glStencilFunc(func, ref, mask);
}

void OpenGLRenderCommand::SetStencilMask(bool enable, CullFace cull_face) {
  if (enable) {
    glStencilMask(0xff);
  } else {
    glStencilMask(0x00);
  }
}

void OpenGLRenderCommand::SetStencilOp(bool enable, CullFace cull_face) {
  if (enable) {
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  }
}

void OpenGLRenderCommand::SetBackCullTest(bool enable) {
  if (enable) {
    glEnable(GL_CULL_FACE);
  } else {
    glDisable(GL_CULL_FACE);
  }
}

void OpenGLRenderCommand::SetBackCullFace(CullFace cull_face) {
  GLenum mode{};
  switch (cull_face) {
    case CullFace::kFront:
      mode = GL_FRONT;
      break;
    case CullFace::kBack:
      mode = GL_BACK;
      break;
    case CullFace::kFrontAndBack:
      mode = GL_FRONT_AND_BACK;
      break;
  }
  glCullFace(mode);
}

void OpenGLRenderCommand::SetBlendColor(const glm::vec4& color) { glBlendColor(color.r, color.g, color.b, color.a); }

void OpenGLRenderCommand::SetBlendFunc(BlendFactor sfactor, BlendFactor dfactor, CullFace cull_face) {
  GLenum sfactor_gl{}, dfactor_gl{};

  switch (sfactor) {
    case BlendFactor::kZero:
      sfactor_gl = GL_ZERO;
      break;
    case BlendFactor::kOne:
      sfactor_gl = GL_ONE;
      break;
    case BlendFactor::kSrcColor:
      sfactor_gl = GL_SRC_COLOR;
      break;
    case BlendFactor::kOneMinusSrcColor:
      sfactor_gl = GL_ONE_MINUS_SRC_COLOR;
      break;
    case BlendFactor::kDstColor:
      sfactor_gl = GL_DST_COLOR;
      break;
    case BlendFactor::kOneMinusDstColor:
      sfactor_gl = GL_ONE_MINUS_DST_COLOR;
      break;
    case BlendFactor::kSrcAlpha:
      sfactor_gl = GL_SRC_ALPHA;
      break;
    case BlendFactor::kOneMinusSrcAlpha:
      sfactor_gl = GL_ONE_MINUS_SRC_ALPHA;
      break;
    case BlendFactor::kDstAlpha:
      sfactor_gl = GL_DST_ALPHA;
      break;
    case BlendFactor::kOneMinusDstAlpha:
      sfactor_gl = GL_ONE_MINUS_DST_ALPHA;
      break;
    case BlendFactor::kConstantColor:
      sfactor_gl = GL_CONSTANT_COLOR;
      break;
    case BlendFactor::kOneMinusConstantColor:
      sfactor_gl = GL_ONE_MINUS_CONSTANT_COLOR;
      break;
    case BlendFactor::kConstantAlpha:
      sfactor_gl = GL_CONSTANT_ALPHA;
      break;
    case BlendFactor::kOneMinusConstantAlpha:
      sfactor_gl = GL_ONE_MINUS_CONSTANT_ALPHA;
      break;
  }

  switch (dfactor) {
    case BlendFactor::kZero:
      dfactor_gl = GL_ZERO;
      break;
    case BlendFactor::kOne:
      dfactor_gl = GL_ONE;
      break;
    case BlendFactor::kSrcColor:
      dfactor_gl = GL_SRC_COLOR;
      break;
    case BlendFactor::kOneMinusSrcColor:
      dfactor_gl = GL_ONE_MINUS_SRC_COLOR;
      break;
    case BlendFactor::kDstColor:
      dfactor_gl = GL_DST_COLOR;
      break;
    case BlendFactor::kOneMinusDstColor:
      dfactor_gl = GL_ONE_MINUS_DST_COLOR;
      break;
    case BlendFactor::kSrcAlpha:
      dfactor_gl = GL_SRC_ALPHA;
      break;
    case BlendFactor::kOneMinusSrcAlpha:
      dfactor_gl = GL_ONE_MINUS_SRC_ALPHA;
      break;
    case BlendFactor::kDstAlpha:
      dfactor_gl = GL_DST_ALPHA;
      break;
    case BlendFactor::kOneMinusDstAlpha:
      dfactor_gl = GL_ONE_MINUS_DST_ALPHA;
      break;
    case BlendFactor::kConstantColor:
      dfactor_gl = GL_CONSTANT_COLOR;
      break;
    case BlendFactor::kOneMinusConstantColor:
      dfactor_gl = GL_ONE_MINUS_CONSTANT_COLOR;
      break;
    case BlendFactor::kConstantAlpha:
      dfactor_gl = GL_CONSTANT_ALPHA;
      break;
    case BlendFactor::kOneMinusConstantAlpha:
      dfactor_gl = GL_ONE_MINUS_CONSTANT_ALPHA;
      break;
  }

  glBlendFunc(sfactor_gl, dfactor_gl);
}

void OpenGLRenderCommand::SetBlendEquation(BlendEquationMode mode, CullFace cull_face) {
  GLenum mode_gl{};

  switch (mode) {
    case BlendEquationMode::kAdd:
      mode_gl = GL_FUNC_ADD;
      break;
    case BlendEquationMode::kSubtract:
      mode_gl = GL_FUNC_SUBTRACT;
      break;
    case BlendEquationMode::kReverseSubtract:
      mode_gl = GL_FUNC_REVERSE_SUBTRACT;
      break;
    case BlendEquationMode::kMin:
      mode_gl = GL_MIN;
      break;
    case BlendEquationMode::kMax:
      mode_gl = GL_MAX;
      break;
  }

  glBlendEquation(mode_gl);
}

void OpenGLRenderCommand::SetDepthRange(float near_val, float far_val) { glDepthRange(near_val, far_val); }

void OpenGLRenderCommand::SetTopolgy(Topology topology) {
  switch (topology) {
    case Topology::kPoint:
      topology_type = GL_POINT;
      break;
    case Topology::kLines:
      topology_type = GL_LINES;
      break;
    case Topology::kLineStrip:
      topology_type = GL_LINE_STRIP;
      break;
    case Topology::kTriangle:
      topology_type = GL_TRIANGLES;
      break;
    case Topology::kTrangleStrip:
      topology_type = GL_TRIANGLE_STRIP;
      break;
    default:
      CORE_ASSERT(false, "Invalid Topology Type.");
      break;
  }
}
}  // namespace genesis
