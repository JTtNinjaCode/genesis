#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "core/renderer/shader.h"
namespace genesis {
class ShaderLibrary {
 public:
  static void Init();

  // void AddShader(const std::string& shader_name,
  //                const std::shared_ptr<Shader>& shader);
  static void AddShader(const std::string& shader_name, const std::string& vertex_shader_file_path,
                        const std::string& fragment_shader_file_path);
  static Shader& GetShader(const std::string& shader_name);
  static void RemoveShader(const std::string& shader_name);

 private:
  ShaderLibrary() = default;
  static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_;
};

}  // namespace genesis