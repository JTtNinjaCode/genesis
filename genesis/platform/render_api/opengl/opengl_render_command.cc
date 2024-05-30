#include "opengl_render_command.h"

#include <glad/glad.h>

#include "core/log/log.h"
namespace genesis {
void OpenGLRenderCommand::SetClearColor(glm::vec4 color) { glClearColor(color.x, color.y, color.z, color.w); }

void OpenGLRenderCommand::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void OpenGLRenderCommand::DrawIndexed(const VertexArray& vertex_array) {
  glDrawElements(GL_TRIANGLES, vertex_array.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderCommand::DrawArray(const VertexArray& vertex_array) {
  glDrawArrays(GL_TRIANGLES, 0, vertex_array.GetVertexCount());
}

void OpenGLRenderCommand::SetBlend(bool enable) {
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
  } else {
    CORE_ASSERT(false, "Invalid drawmode in OpenGLRenderCommand.");
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
void OpenGLRenderCommand::SetStencilFunc(StencilFunc stencil_fun, int value1, int value2, CullFace cull_face) {
  if (stencil_fun == StencilFunc::kAlways) {
    glStencilFunc(GL_ALWAYS, value1, value2);
  } else if (stencil_fun == StencilFunc::kEqual) {
    glStencilFunc(GL_EQUAL, value1, value2);
  } else if (stencil_fun == StencilFunc::kGreater) {
    glStencilFunc(GL_GREATER, value1, value2);
  } else if (stencil_fun == StencilFunc::kGreaterEqual) {
    glStencilFunc(GL_GEQUAL, value1, value2);
  } else if (stencil_fun == StencilFunc::kLessEqual) {
    glStencilFunc(GL_LEQUAL, value1, value2);
  } else if (stencil_fun == StencilFunc::kNever) {
    glStencilFunc(GL_NEVER, value1, value2);
  } else if (stencil_fun == StencilFunc::kNotEqual) {
    glStencilFunc(GL_NOTEQUAL, value1, value2);
  }
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
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
  }
}
void OpenGLRenderCommand::SetBackCullTest(bool enable) {
  if (enable) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
  } else {
    glDisable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
  }
}
void OpenGLRenderCommand::SetBackCullFace(CullFace cull_face) {
  if (cull_face == CullFace::kFront) {
    glCullFace(GL_FRONT);
  } else if (cull_face == CullFace::kBack) {
    glCullFace(GL_BACK);
  } else if (cull_face == CullFace::kFrontAndBack) {
    glCullFace(GL_FRONT_AND_BACK);
  }
}
}  // namespace genesis
