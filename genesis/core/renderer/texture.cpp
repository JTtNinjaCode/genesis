#include "texture.h"

#include "core/log/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_texture.h"
namespace genesis {
std::shared_ptr<Texture2D> Texture2D::Create(
    const std::filesystem::path& path) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture2D>(path);
  }
  CORE_ASSERT(false, "valid render api.");
  return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::Create(unsigned char* data,
                                             unsigned int channels,
                                             unsigned int width,
                                             unsigned int height) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture2D>(data, channels, width, height);
  }
  CORE_ASSERT(false, "valid render api.");
  return nullptr;
}
}  // namespace genesis
