#include "opengl_buffer.h"

#include <glad/glad.h>
namespace genesis {
OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, size_t size) {
  glCreateBuffers(1, &id_);
  glNamedBufferData(id_, size, vertices, GL_STATIC_DRAW);
  size_ = size;
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &id_); }

void OpenGLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id_); }

void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

const void* OpenGLVertexBuffer::GetId() const { return reinterpret_cast<const void*>(&id_); }

void OpenGLVertexBuffer::SubData(void* vertices, size_t size) { glNamedBufferSubData(id_, 0, size, vertices); }

size_t OpenGLVertexBuffer::GetSize() const { return size_; }

OpenGLIndexBuffer::OpenGLIndexBuffer(void* vertices, size_t size) {
  glCreateBuffers(1, &id_);
  glNamedBufferData(id_, size, vertices, GL_STATIC_DRAW);
  count_ = size / sizeof(unsigned int);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &id_); }

unsigned int OpenGLIndexBuffer::GetCount() const { return count_; }

void OpenGLIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }

void OpenGLIndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

const void* OpenGLIndexBuffer::GetId() const { return reinterpret_cast<const void*>(&id_); }

void OpenGLIndexBuffer::SubData(void* vertices, size_t size) { glNamedBufferSubData(id_, 0, size, vertices); }

OpenGLUniformBuffer::OpenGLUniformBuffer(void* vertices, size_t size) {
  glCreateBuffers(1, &id_);
  glNamedBufferData(id_, size, vertices, GL_STATIC_DRAW);
}

OpenGLUniformBuffer::~OpenGLUniformBuffer() { glDeleteBuffers(1, &id_); }

unsigned int OpenGLUniformBuffer::GetCount() const { return count_; }

void OpenGLUniformBuffer::BindSlot(const unsigned int slot) const { glBindBufferBase(GL_UNIFORM_BUFFER, slot, id_); }

void OpenGLUniformBuffer::Bind() const { glBindBuffer(GL_UNIFORM_BUFFER, id_); }

void OpenGLUniformBuffer::Unbind() const { glBindBuffer(GL_UNIFORM_BUFFER, 0); }

const void* OpenGLUniformBuffer::GetId() const { return reinterpret_cast<const void*>(&id_); }

void OpenGLUniformBuffer::SubData(void* vertices, size_t size, size_t begin) {
  glNamedBufferSubData(id_, begin, size, vertices);
}

}  // namespace genesis