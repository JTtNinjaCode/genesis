#pragma once
#include <memory>

#include "render_buffer.h"
#include "texture.h"
namespace genesis {
class FrameBuffer {
 public:
  static std::shared_ptr<FrameBuffer> Create();
  static void BindDefaultFrameBuffer();

  virtual ~FrameBuffer() {}
  // texture, cant be accessed from shader
  virtual void BindTexture(const std::shared_ptr<Texture> &texture) = 0;  // add usage
  // render buffer, cant be accessed from shader
  virtual void BindRendererBuffer(const std::shared_ptr<RenderBuffer> &render_buffer) = 0;
  virtual void Bind() const = 0;
  virtual const void *GetId() const = 0;
};
}  // namespace genesis