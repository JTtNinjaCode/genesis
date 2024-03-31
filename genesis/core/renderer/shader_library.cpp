#include "shader_library.h"

#include "core/log/log.h"
namespace genesis {
std::unique_ptr<ShaderLibrary> ShaderLibrary::instance_;

ShaderLibrary& ShaderLibrary::GetInstance() {
  if (!instance_) {
    instance_ = std::make_unique<ShaderLibrary>();
  }
  return *instance_;
}

void ShaderLibrary::AddShader(const std::string& shader_name,
                              const std::string& vertex_shader_file_path,
                              const std::string& fragment_shader_file_path) {
  std::shared_ptr<Shader> shader =
      Shader::Create(vertex_shader_file_path, fragment_shader_file_path);
  CORE_ASSERT(shaders_.find(shader_name) == shaders_.end(),
              "Shader already exists in library.");
  shaders_.insert({shader_name, shader});
}

Shader& ShaderLibrary::GetShader(std::string shader_name) {
  CORE_ASSERT(shaders_.find(shader_name) != shaders_.end(),
              "Cant Find Shader with shader name:{0}.", shader_name);
  return *shaders_[shader_name];
}

}  // namespace genesis