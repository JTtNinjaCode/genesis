#include "shader.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include "core/log/log.h"
#include "core/renderer/renderer_api.h"
#include "platform/render_api/opengl/opengl_shader.h"

namespace genesis {
std::shared_ptr<Shader> Shader::Create(
    const std::string& vertex_file_path, const std::string& fragment_file_path,
    const std::string& geometry_file_path) {
  std::ifstream vertex_file(vertex_file_path);
  std::ifstream fragment_file(fragment_file_path);
  std::ifstream geometry_file(geometry_file_path);

  if (!vertex_file || !fragment_file) {
    CORE_LOG_ERROR("failed to open file.");
  }

  std::string vertex_source;
  vertex_file.seekg(0, std::ios::end);
  vertex_source.resize(vertex_file.tellg());
  vertex_file.seekg(0, std::ios::beg);
  vertex_file.read(&vertex_source[0], vertex_source.size());
  vertex_file.close();

  std::string fragment_source;
  fragment_file.seekg(0, std::ios::end);
  fragment_source.resize(fragment_file.tellg());
  fragment_file.seekg(0, std::ios::beg);
  fragment_file.read(&fragment_source[0], fragment_source.size());
  fragment_file.close();

  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLShader>(vertex_source, fragment_source);
  }
  CORE_ASSERT(false, "invliad api.");
  return nullptr;
}

}  // namespace genesis