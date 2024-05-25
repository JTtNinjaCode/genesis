#include "texture.h"

#include "core/log/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_texture.h"
namespace genesis {
std::shared_ptr<Texture2D> Texture2D::Create(const std::filesystem::path& path, TextureType texture_type) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture2D>(path);
  }
  CORE_ASSERT(false, "valid render api.");
  return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::Create(unsigned char* data, TextureFormat data_format, unsigned int width,
                                             unsigned int height, TextureType texture_type) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture2D>(data, data_format, width, height);
  }
  CORE_ASSERT(false, "valid render api.");
  return nullptr;
}
std::shared_ptr<Texture3D> Texture3D::Create(const std::vector<std::filesystem::path>& faces_path,
                                             TextureType texture_type) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture3D>(faces_path);
  }
  CORE_ASSERT(false, "valid render api.");
  return nullptr;
}
}  // namespace genesis
