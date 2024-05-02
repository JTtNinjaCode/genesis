#pragma once
#include <string>

#include "core/renderer/shader.h"
namespace genesis {
class OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string& vertex_source,
               const std::string& fragment_source);
  virtual ~OpenGLShader();
  void Bind() const override;
  void Unbind() const override;
  void SetUniform(const std::string& name, const glm::mat4& value) override;
  void SetUniform(const std::string& name, const glm::vec4& value) override;
  void SetUniform(const std::string& name, const glm::vec3& value) override;
  void SetUniform(const std::string& name, const glm::vec2& value) override;
  void SetUniform(const std::string& name, const int value) override;
  void SetUniform(const std::string& name, const float value) override;
  void SetUniform(const std::string& name, const bool value) override;

 private:
  unsigned int id_ = 0;
};

}  // namespace genesis