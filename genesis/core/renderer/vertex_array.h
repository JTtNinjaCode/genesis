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

  virtual void AddVertexBuffer(const VertexBuffer& vertex_buffer) = 0;
  virtual void SetIndexBuffer(const IndexBuffer& index_buffer) = 0;
  bool HasIndex() const { return has_index_; }
  unsigned int GetCount() const { return count_; }
  bool GetIndexBuffer() const { return has_index_; }
  static std::shared_ptr<VertexArray>Create(const BufferLayout& buffer_layout);

 protected:
  bool has_index_ = false;
  unsigned int count_ = 0;
};

}  // namespace genesis