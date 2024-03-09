#include "shader.h"

#include <core/log.h>
#include <glad/glad.h>

#include <vector>
genesis::Shader::Shader(const std::string &vertex_source,
                        const std::string &fragment_source) {
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  const GLchar *source = (const GLchar *)vertex_source.c_str();
  glShaderSource(vertex_shader, 1, &source, 0);
  glCompileShader(vertex_shader);

  GLint isCompiled = 0;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> info_log(maxLength);
    glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &info_log[0]);
    CORE_LOG_ERROR("Fail to Compile Vertex Shader.");
    CORE_LOG_ERROR("{0}", info_log.data());

    glDeleteShader(vertex_shader);
    return;
  }

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  source = (const GLchar *)fragment_source.c_str();
  glShaderSource(fragment_shader, 1, &source, 0);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> info_log(maxLength);
    glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &info_log[0]);
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

  GLint isLinked = 0;
  glGetProgramiv(id_, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> info_log(maxLength);
    glGetProgramInfoLog(id_, maxLength, &maxLength, &info_log[0]);

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

genesis::Shader::~Shader() { glDeleteProgram(id_); }

void genesis::Shader::Bind() const { glUseProgram(id_); }

void genesis::Shader::Unbind() const { glUseProgram(0); }
