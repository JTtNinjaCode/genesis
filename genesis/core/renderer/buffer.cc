#include "buffer.h"

#include "core/log/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_buffer.h"
namespace genesis {

std::shared_ptr<VertexBuffer> VertexBuffer::Create(void* vertices, size_t size) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLVertexBuffer>(vertices, size);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
  return nullptr;
}
std::shared_ptr<IndexBuffer> IndexBuffer::Create(void* vertices, size_t size) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLIndexBuffer>(vertices, size);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
  return nullptr;
}
std::shared_ptr<UniformBuffer> UniformBuffer::Create(void* vertices, size_t size) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLUniformBuffer>(vertices, size);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
  return nullptr;
}
std::shared_ptr<ShaderStorageBuffer> ShaderStorageBuffer::Create(void* vertices, size_t size) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLShaderStorageBuffer>(vertices, size);
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
  return nullptr;
}
}  // namespace genesis
