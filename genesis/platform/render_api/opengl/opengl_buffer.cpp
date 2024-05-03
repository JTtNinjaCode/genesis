#include "opengl_buffer.h"

#include <glad/glad.h>
namespace genesis {
OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, size_t size) {
  glCreateBuffers(1, &id_);
  glNamedBufferData(id_, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &id_); }

void OpenGLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id_); }

void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

int OpenGLVertexBuffer::GetId() const { return id_; }

void OpenGLVertexBuffer::SubData(void* vertices, size_t size) { glNamedBufferSubData(id_, 0, size, vertices); }

OpenGLIndexBuffer::OpenGLIndexBuffer(void* vertices, size_t size) {
  glCreateBuffers(1, &id_);
  glNamedBufferData(id_, size, vertices, GL_STATIC_DRAW);
  count_ = size / sizeof(unsigned int);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &id_); }

void OpenGLIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }

void OpenGLIndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

int OpenGLIndexBuffer::GetId() const { return id_; }

void OpenGLIndexBuffer::SubData(void* vertices, size_t size) { glNamedBufferSubData(id_, 0, size, vertices); }

}  // namespace genesis