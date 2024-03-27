#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>
namespace genesis {
class Shader {
 public:
  static std::shared_ptr<Shader> Create(
      const std::string& vertex_file_path, const std::string& fragment_file_path,
      const std::string& geometry_file_path = "");

  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  // virtual void SetUniform(const std::string& name, const glm::mat4 value) =
  // 0;

 private:
  unsigned int id_ = 0;
};
}  // namespace genesis
