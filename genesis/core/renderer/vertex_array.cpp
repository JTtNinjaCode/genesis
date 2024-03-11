#include "vertex_array.h"

#include <memory>

#include "core/log.h"
#include "core/renderer/renderer.h"
#include "platform/render_api/opengl/opengl_vertex_array.h"
namespace genesis {
std::shared_ptr<VertexArray> VertexArray::Create(
    const BufferLayout& buffer_layout) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLVertexArray>(buffer_layout);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
  return nullptr;
}
}  // namespace genesis