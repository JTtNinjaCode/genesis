#include "opengl_shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "core/log/log.h"
namespace genesis {
OpenGLShader::OpenGLShader(const std::string &vertex_source, const std::string &fragment_source) {
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  const GLchar *source = (const GLchar *)vertex_source.c_str();
  glShaderSource(vertex_shader, 1, &source, 0);
  glCompileShader(vertex_shader);

  GLint is_compiled = 0;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glGetShaderInfoLog(vertex_shader, max_length, &max_length, &info_log[0]);
    CORE_LOG_ERROR("Fail to Compile Vertex Shader.");
    CORE_LOG_ERROR("{0}", info_log.data());

    glDeleteShader(vertex_shader);
    return;
  }

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  source = (const GLchar *)fragment_source.c_str();
  glShaderSource(fragment_shader, 1, &source, 0);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glGetShaderInfoLog(fragment_shader, max_length, &max_length, &info_log[0]);
    CORE_LOG_ERROR("Fail to Compile Fragment Shader.");
    CORE_LOG_ERROR("{0}", info_log.data());
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return;
  }

  id_ = glCreateProgram();
  glAttachShader(id_, vertex_shader);
  glAttachShader(id_, fragment_shader);

  glLinkProgram(id_);

  GLint is_linked = 0;
  glGetProgramiv(id_, GL_LINK_STATUS, (int *)&is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glGetProgramInfoLog(id_, max_length, &max_length, &info_log[0]);

    glDeleteProgram(id_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    CORE_LOG_ERROR("Fail to Compile Vertex Shader.");
    CORE_LOG_ERROR("{0}", info_log.data());
    return;
  }
  glDetachShader(id_, vertex_shader);
  glDetachShader(id_, fragment_shader);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(id_); }

void OpenGLShader::Bind() const { glUseProgram(id_); }

void OpenGLShader::Unbind() const { glUseProgram(0); }

void OpenGLShader::SetUniform(const std::string &name, const glm::mat4 &value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glProgramUniformMatrix4fv(id_, location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::SetUniform(const std::string &name, const glm::vec4 &value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glProgramUniform4f(id_, location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetUniform(const std::string &name, const glm::vec3 &value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glProgramUniform3f(id_, location, value.x, value.y, value.z);
}

void OpenGLShader::SetUniform(const std::string &name, const glm::vec2 &value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glProgramUniform2f(id_, location, value.x, value.y);
}

void OpenGLShader::SetUniform(const std::string &name, const int value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glProgramUniform1i(id_, location, value);
}

void OpenGLShader::SetUniform(const std::string &name, const float value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glProgramUniform1f(id_, location, value);
}

void OpenGLShader::SetUniform(const std::string &name, const bool value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glProgramUniform1i(id_, location, value);
}

void OpenGLShader::SetUniformBlock(const std::string &name, const unsigned int slot) {
  GLint location = glGetUniformBlockIndex(id_, name.c_str());
  glUniformBlockBinding(id_, location, slot);
}
}  // namespace genesis
