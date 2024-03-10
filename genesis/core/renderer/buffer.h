#pragma once
#include <memory>
namespace genesis {
class VertexBuffer {
 public:
  static std::shared_ptr<VertexBuffer> Create(void *vertices, size_t size);

  virtual ~VertexBuffer() {}
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
};

class IndexBuffer {
 public:
  static std::shared_ptr<IndexBuffer> Create(void *vertices, size_t size);
  unsigned int GetCount() const { return count; }
  virtual ~IndexBuffer() {}
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

 protected:
  unsigned int count = 0;
};

}  // namespace genesis