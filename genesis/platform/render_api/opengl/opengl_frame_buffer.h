#pragma once
#include "core/renderer/frame_buffer.h"
namespace genesis {
class OpenGLFrameBuffer : public FrameBuffer {
 public:
  static void BindDefaultFrameBuffer();
  OpenGLFrameBuffer();
  ~OpenGLFrameBuffer();
  void BindTexture(const Texture2D& texture, unsigned int index, AttachmentType attachment_type) override;
  void BindRendererBuffer(const RenderBuffer& render_buffer, unsigned int index,
                          AttachmentType attachment_type) override;
  void Bind() const override;
  const void* GetId() const override;

 private:
  unsigned int id_ = 0;
};
}  // namespace genesis