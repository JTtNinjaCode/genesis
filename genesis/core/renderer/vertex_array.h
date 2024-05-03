#pragma once
#include <memory>

#include "core/math_struct.h"
#include "core/renderer/buffer.h"
#include "core/renderer/buffer_layout.h"

namespace genesis {
class VertexArray {
 public:
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer> vertex_buffer) = 0;
  virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> index_buffer) = 0;
  virtual VertexBuffer& GetVertexBuffer() const = 0;
  virtual IndexBuffer& GetIndexBuffer() const = 0;

  bool HasIndex() const { return has_index_; }
  virtual unsigned int GetCount() const = 0;
  static std::shared_ptr<VertexArray> Create(const BufferLayout& buffer_layout);

 protected:
  bool has_index_ = false;
};

}  // namespace genesis