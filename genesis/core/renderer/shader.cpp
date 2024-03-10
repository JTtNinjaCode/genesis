#include "shader.h"

#include "platform/render_api/opengl/opengl_shader.h"

namespace genesis {
std::shared_ptr<Shader> Shader::Create(const std::string &vertex_source,
                                       const std::string &fragment_source) {
  return std::make_shared<OpenGLShader>(vertex_source, fragment_source);
}

}  // namespace genesis