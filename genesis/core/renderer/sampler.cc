#include "sampler.h"

#include "core/log/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_sampler.h"
namespace genesis {
std::shared_ptr<Sampler> Sampler::Create() {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLSampler>();
      break;
    default:
      CORE_ASSERT(false, "Not Valid RenderAPI.");
  }
  return nullptr;
}
}  // namespace genesis