#include "render_command.h"

#include "core/log/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_render_command.h"
namespace genesis {
std::shared_ptr<RenderCommand> RenderCommand::render_command_ = nullptr;
RenderCommand& RenderCommand::GetInstanced() {
  if (!render_command_) {
    switch (RendererAPI::GetAPI()) {
      case RendererAPI::API::OpenGL:
        render_command_ = std::make_shared<OpenGLRenderCommand>();
        break;
      default:
        CORE_ASSERT(false, "Not Valid API.");
    }
    render_command_->SetDepthTest(true);
  }
  return *render_command_;
}
}  // namespace genesis
