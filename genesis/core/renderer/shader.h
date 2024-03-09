#pragma once
#include <string>
namespace genesis {
class Shader {
 public:
  Shader(const std::string& vertex_source, const std::string& fragment_source);
  ~Shader();

  void Bind() const;
  void Unbind() const;

 private:
  unsigned int id_ = 0;
};
}  // namespace genesis
