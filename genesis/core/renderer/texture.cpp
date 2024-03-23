#include "texture.h"

#include "core/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_texture.h"
namespace genesis {
std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture2D>(path);
  }
  CORE_ASSERT(false, "valid render api.");
  return nullptr;
}
}  // namespace genesis
