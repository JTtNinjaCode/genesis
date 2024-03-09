#include "Renderer.h"
namespace genesis {
RenderAPI Renderer::api_ = RenderAPI::OpenGL;
RenderAPI Renderer::GetAPI() { return api_; }
}  // namespace genesis
