#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>
namespace genesis {
class Shader {
 public:
  static std::shared_ptr<Shader> Create(const std::string& vertex_source,
                                        const std::string& fragment_source);
  virtual ~Shader(){};

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual void SetUniform(const std::string& name, const glm::mat4 value) = 0;

 private:
  unsigned int id_ = 0;
};
}  // namespace genesis
