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

 private:
  unsigned int id_ = 0;
};

}  // namespace genesis