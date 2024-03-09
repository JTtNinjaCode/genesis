#pragma once
#include "core/math_struct.h"
#include "core/renderer/buffer.h"
#include "core/renderer/buffer_layout.h"

#include <memory>

namespace genesis {
class VertexArray {
 public:
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void AddVertexBuffer(const VertexBuffer& vertex_buffer) = 0;
  virtual void SetIndexBuffer(const IndexBuffer& index_buffer) = 0;
  static VertexArray* Create(const BufferLayout& buffer_layout);
};

}  // namespace genesis