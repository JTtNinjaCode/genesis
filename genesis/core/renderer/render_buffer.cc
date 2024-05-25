#include "render_buffer.h"

#include "buffer.h"
#include "core/log/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_render_buffer.h"
namespace genesis {
std::shared_ptr<RenderBuffer> RenderBuffer::Create(unsigned int width, unsigned int height) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLRenderBuffer>(width, height);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
  return nullptr;
}
}  // namespace genesis
