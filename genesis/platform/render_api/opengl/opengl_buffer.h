#pragma once
#include "core/renderer/buffer.h"
namespace genesis {
class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(void *vertices, size_t size);
  ~OpenGLVertexBuffer();
  void Bind() const override;
  void Unbind() const override;
  int GetId() const override;
  void SubData(void *vertices, size_t size) override;

 private:
  unsigned int id_ = 0;
};

class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(void *vertices, size_t size);
  ~OpenGLIndexBuffer();
  void Bind() const override;
  void Unbind() const override;
  int GetId() const override;
  void SubData(void *vertices, size_t size) override;

 private:
  unsigned int id_ = 0;
};

class OpenGLUniformBuffer : public UniformBuffer {
 public:
  OpenGLUniformBuffer(void *vertices, size_t size);
  ~OpenGLUniformBuffer();
  void BindSlot(const unsigned int slot = 0) const override;
  void Bind() const override;
  void Unbind() const override;
  int GetId() const override;
  void SubData(void *vertices, size_t size, size_t begin = 0) override;

 private:
  unsigned int id_ = 0;
};
}  // namespace genesis