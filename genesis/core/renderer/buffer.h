#pragma once
#include <memory>
namespace genesis {
class VertexBuffer {
 public:
  static std::shared_ptr<VertexBuffer> Create(void *vertices, size_t size);

  virtual ~VertexBuffer() {}
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual const void *GetId() const = 0;
  virtual size_t GetSize() const = 0;
  virtual void SubData(void *vertices, size_t size) = 0;
};

class IndexBuffer {
 public:
  static std::shared_ptr<IndexBuffer> Create(void *vertices, size_t size);
  virtual ~IndexBuffer() {}
  virtual unsigned int GetCount() const = 0;
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual const void *GetId() const = 0;
  virtual void SubData(void *vertices, size_t size) = 0;
};

class UniformBuffer {
 public:
  static std::shared_ptr<UniformBuffer> Create(void *vertices, size_t size);
  virtual ~UniformBuffer() {}
  virtual unsigned int GetCount() const = 0;
  virtual void BindSlot(const unsigned int slot) const = 0;
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual const void *GetId() const = 0;
  virtual void SubData(void *vertices, size_t size, size_t begin = 0) = 0;
};

class ShaderStorageBuffer {
 public:
  static std::shared_ptr<ShaderStorageBuffer> Create(void *vertices, size_t size);
  virtual ~ShaderStorageBuffer() {}
  virtual void BindSlot(const unsigned int slot) const = 0;
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual const void *GetId() const = 0;
  virtual void SubData(void *vertices, size_t size, size_t begin = 0) = 0;
};

}  // namespace genesis