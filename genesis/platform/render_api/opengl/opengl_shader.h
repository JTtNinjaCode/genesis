#pragma once
#include <string>

#include "core/renderer/shader.h"
namespace genesis {
class OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string &vertex_source,
               const std::string &fragment_source);
  virtual ~OpenGLShader();
  void Bind() const override;
  void Unbind() const override;

 private:
  unsigned int id_;
};

}  // namespace genesis