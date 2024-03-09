#include "buffer.h"

#include <core/log.h>
#include <core/renderer/renderer.h>
#include <platform/render_api/opengl/opengl_buffer.h>
namespace genesis {

VertexBuffer* VertexBuffer::Create(void* vertices, size_t size) {
  switch (Renderer::GetAPI()) {
    case RenderAPI::OpenGL:
      return new OpenGLVertexBuffer(vertices, size);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
}
IndexBuffer* IndexBuffer::Create(void* vertices, size_t size) {
  switch (Renderer::GetAPI()) {
    case RenderAPI::OpenGL:
      return new OpenGLIndexBuffer(vertices, size);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
}
}  // namespace genesis
