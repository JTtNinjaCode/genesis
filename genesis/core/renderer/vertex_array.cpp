#include "vertex_array.h"


#include "core/log.h"
#include "core/renderer/renderer.h"
#include "platform/render_api/opengl/opengl_vertex_array.h"
namespace genesis {
VertexArray* VertexArray::Create(const BufferLayout& buffer_layout) {
  switch (Renderer::GetAPI()) {
    case RenderAPI::OpenGL:
      return new OpenGLVertexArray(buffer_layout);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
}
}  // namespace genesis