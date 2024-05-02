#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "core/renderer/vertex_array.h"
namespace genesis {
enum class DrawMode {
	kFill, kLine, kPoint
};
class RenderCommand {
 public:
  static RenderCommand& GetInstanced();

  virtual void SetClearColor(glm::vec4 color) = 0;
  virtual void Clear() = 0;
  virtual void DrawIndexed(const VertexArray& vertex_array) = 0;
  virtual void SetBlend(bool enable) = 0;
  virtual void SetDepthTest(bool enable) = 0;
  virtual void SetViewport(int x, int y, int width, int height) = 0;
  virtual void SetDrawMode(DrawMode enable) = 0;
  virtual void SetBackCulling(bool enable) = 0;

 private:
  static std::shared_ptr<RenderCommand> render_command_;
};
}  // namespace genesis
