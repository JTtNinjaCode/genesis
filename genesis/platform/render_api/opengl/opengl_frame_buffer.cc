#include "opengl_frame_buffer.h"

#include <glad/glad.h>
namespace genesis {
void OpenGLFrameBuffer::BindDefaultFrameBuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
OpenGLFrameBuffer::OpenGLFrameBuffer() { 
    glCreateFramebuffers(1, &id_); }
OpenGLFrameBuffer::~OpenGLFrameBuffer() { glDeleteFramebuffers(1, &id_); }

void OpenGLFrameBuffer::BindTexture(const Texture2D& texture, unsigned int index, AttachmentType attachment_type) {
  if (attachment_type == AttachmentType::kColor) {
    glNamedFramebufferTexture(id_, GL_COLOR_ATTACHMENT0 + index, *(const GLuint*)texture.GetID(), 0);
  } else if (attachment_type == AttachmentType::kDepthStencil) {
    glNamedFramebufferTexture(id_, GL_DEPTH_STENCIL_ATTACHMENT, *(const GLuint*)texture.GetID(), 0);
  }

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
  }
}

void OpenGLFrameBuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, id_); }
const void* OpenGLFrameBuffer::GetId() const { return reinterpret_cast<const void*>(&id_); }
void OpenGLFrameBuffer::BindRendererBuffer(const RenderBuffer& render_buffer, unsigned int index,
                                           AttachmentType attachment_type) {
  if (attachment_type == AttachmentType::kColor) {
    glNamedFramebufferRenderbuffer(id_, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER,
                                   *(const GLuint*)render_buffer.GetId());
  } else if (attachment_type == AttachmentType::kDepthStencil) {
    glNamedFramebufferRenderbuffer(id_, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                                   *(const GLuint*)render_buffer.GetId());
  }
}
}  // namespace genesis