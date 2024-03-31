#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "core/renderer/shader.h"
namespace genesis {
class ShaderLibrary {
  friend std::unique_ptr<ShaderLibrary> std::make_unique<ShaderLibrary>();

 public:
  static ShaderLibrary& GetInstance();

  // void AddShader(const std::string& shader_name,
  //                const std::shared_ptr<Shader>& shader);
  void AddShader(const std::string& shader_name,
                 const std::string& vertex_shader_file_path,
                 const std::string& fragment_shader_file_path);
  Shader& GetShader(std::string shader_name);

 private:
  ShaderLibrary() = default;
  static std::unique_ptr<ShaderLibrary> instance_;

  std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_;
};

}  // namespace genesis