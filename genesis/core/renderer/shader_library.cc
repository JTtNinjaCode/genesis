#include "shader_library.h"

#include <glad/glad.h>

#include <fstream>
#include <iostream>

#include "core/log/log.h"
#include "core/renderer/shader_header_path.h"
namespace genesis {
std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderLibrary::shaders_;

static void ReadFile(const std::filesystem::path& path) {
  // replace slash
  std::string path_string = path.string();
  std::replace(path_string.begin(), path_string.end(), '\\', '/');
  std::ifstream file(path, std::ios::ate);
  if (!file.is_open()) {
    CORE_LOG_ERROR("Failed to open file:");
  }
  size_t size = file.tellg();
  std::string source(size, ' ');
  file.seekg(0);
  file.read(source.data(), size);
  glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1, (std::string("/") + path_string).c_str(), -1, source.c_str());
}
static void TraverDirectory(const std::filesystem::path& dir_path,
                            const std::function<void(const std::filesystem::path&)>& func) {
  if (std::filesystem::exists(dir_path) && std::filesystem::is_directory(dir_path)) {
    for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
      if (std::filesystem::is_directory(entry.status())) {
        TraverDirectory(entry.path(), func);
      } else if (std::filesystem::is_regular_file(entry.status())) {
        if (entry.path().extension() == ".glsl") {
          func(entry.path());
        }
      }
    }
  }
}

// TODO should not implement in abstract layer
void ShaderLibrary::Init() { TraverDirectory("assets/shaders/lygia", ReadFile); }

void ShaderLibrary::AddShader(const std::string& shader_name, const std::string& vertex_shader_file_path,
                              const std::string& fragment_shader_file_path) {
  std::shared_ptr<Shader> shader = Shader::Create(vertex_shader_file_path, fragment_shader_file_path);
  CORE_ASSERT(shaders_.find(shader_name) == shaders_.end(), "Shader already exists in library.");
  shaders_.insert({shader_name, shader});
}

Shader& ShaderLibrary::GetShader(const std::string& shader_name) {
  CORE_ASSERT(shaders_.find(shader_name) != shaders_.end(), "Cant Find Shader with shader name:{0}.", shader_name);
  return *shaders_[shader_name];
}

void ShaderLibrary::RemoveShader(const std::string& shader_name) { shaders_.erase(shader_name); }

}  // namespace genesis