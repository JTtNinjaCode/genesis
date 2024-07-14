#include "opengl_render_buffer.h"

#include <glad/glad.h>

#include "opengl_frame_buffer.h"
namespace genesis {
OpenGLRenderBuffer::OpenGLRenderBuffer(unsigned int width, unsigned int height) {
  glCreateRenderbuffers(1, &id_);
  glNamedRenderbufferStorage(id_, GL_DEPTH24_STENCIL8, width, height);
}
OpenGLRenderBuffer::~OpenGLRenderBuffer() { glDeleteRenderbuffers(1, &id_); }
void OpenGLRenderBuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, id_); }
const void* OpenGLRenderBuffer::GetId() const { return reinterpret_cast<const void*>(&id_); }
}  // namespace genesis