#include "opengl_sampler.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "core/log/log.h"
#include "opengl_shader.h"
namespace genesis {
OpenGLSampler::OpenGLSampler() { glCreateSamplers(1, &id_); }
OpenGLSampler::~OpenGLSampler() { glDeleteSamplers(1, &id_); }
void OpenGLSampler::Bind(unsigned int slot) const { glBindSampler(slot, id_); }
void OpenGLSampler::SetSamplerFunc(unsigned int slot) const {
  glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

  glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

  glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}
void OpenGLSampler::SetWrapFunc(unsigned int slot) const {
  glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
  glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
}
const void *OpenGLSampler::GetId() const { return reinterpret_cast<const void *>(&id_); }
}  // namespace genesis
