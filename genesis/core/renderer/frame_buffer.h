#pragma once
#include <memory>

#include "render_buffer.h"
#include "texture.h"
namespace genesis {
enum class AttachmentType { kColor, kDepthStencil };

class FrameBuffer {
 public:
  static std::shared_ptr<FrameBuffer> Create();
  static void BindDefaultFrameBuffer();

  virtual ~FrameBuffer() {}
  // texture, cant be accessed from shader
  virtual void BindTexture(const Texture2D & texture, unsigned int index,
                           AttachmentType attachment_type) = 0;  // add usage
  // render buffer, cant be accessed from shader
  virtual void BindRendererBuffer(const RenderBuffer &render_buffer, unsigned int index,
                                  AttachmentType attachment_type) = 0;
  virtual void Bind() const = 0;
  virtual const void *GetId() const = 0;
};
}  // namespace genesis