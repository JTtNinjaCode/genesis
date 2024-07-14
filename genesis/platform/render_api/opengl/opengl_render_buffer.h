#pragma once
#include "core/renderer/frame_buffer.h"
namespace genesis {
class OpenGLRenderBuffer : public RenderBuffer {
 public:
  OpenGLRenderBuffer(unsigned int width, unsigned int height);
  ~OpenGLRenderBuffer();
  void Bind() const override;
  const void* GetId() const override;

 private:
  unsigned int id_ = 0;
};
}  // namespace genesis