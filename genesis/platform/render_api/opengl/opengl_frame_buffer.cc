#include "opengl_frame_buffer.h"

#include <glad/glad.h>
namespace genesis {
void OpenGLFrameBuffer::BindDefaultFrameBuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
OpenGLFrameBuffer::OpenGLFrameBuffer() { glCreateBuffers(1, &id_); }
OpenGLFrameBuffer::~OpenGLFrameBuffer() { glDeleteFramebuffers(1, &id_); }

void OpenGLFrameBuffer::BindTexture(const std::shared_ptr<Texture>& texture) {
  texture->Bind(10);  // TODO: why use 10?
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id_, 0);
}

void OpenGLFrameBuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, id_); }
void* OpenGLFrameBuffer::GetId() const { return (void*)&id_; }
void OpenGLFrameBuffer::BindRendererBuffer(const std::shared_ptr<RenderBuffer>& render_buffer) {
  render_buffer->Bind();  // TODO: why use 10?
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id_, 0);
}
}  // namespace genesis