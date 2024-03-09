#pragma once
namespace genesis {
class VertexBuffer {
 public:
  static VertexBuffer *Create(void *vertices, size_t size);

  virtual ~VertexBuffer() {}
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
};
class IndexBuffer {
 public:
  static IndexBuffer *Create(void *vertices, size_t size);

  virtual ~IndexBuffer() {}
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
};

}  // namespace genesis