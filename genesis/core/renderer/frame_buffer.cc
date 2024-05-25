#include "frame_buffer.h"

#include "core/log/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_frame_buffer.h"
namespace genesis {
std::shared_ptr<FrameBuffer> FrameBuffer::Create() {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLFrameBuffer>();
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
  return nullptr;
}
void FrameBuffer::BindDefaultFrameBuffer() {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      OpenGLFrameBuffer::BindDefaultFrameBuffer();  // TODO: optimize DefaultFrameBuffer
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
}
}  // namespace genesis
