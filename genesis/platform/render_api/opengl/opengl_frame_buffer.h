#pragma once
#include "core/renderer/frame_buffer.h"
namespace genesis {
class OpenGLFrameBuffer : public FrameBuffer {
 public:
  static void BindDefaultFrameBuffer();
  OpenGLFrameBuffer();
  ~OpenGLFrameBuffer();
  void BindTexture(const std::shared_ptr<Texture>& texture) override;
  void BindRendererBuffer(const std::shared_ptr<RenderBuffer>& render_buffer) override;
  void Bind() const override;
  const void* GetId() const override;

 private:
  unsigned int id_ = 0;
};
}  // namespace genesis