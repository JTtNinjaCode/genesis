#pragma once
#include <glad/glad.h>

#include <vector>

#include "core/renderer/buffer_layout.h"
#include "core/renderer/vertex_array.h"
namespace genesis {
GLenum MathDataTypeToOpenGLBaseType(MathDataType type);

// only support one vertex buffer. and attrib point to that vertex buffer. and buffer layout cant be modified
class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray(const BufferLayout& buffer_layout);
  virtual ~OpenGLVertexArray();
  void Bind() const override;
  void Unbind() const override;
  unsigned int GetCount() const override;

  void SetVertexBuffer(const std::shared_ptr<VertexBuffer> vertex_buffer) override;
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer> index_buffer) override;
  VertexBuffer& GetVertexBuffer() const override;
  IndexBuffer& GetIndexBuffer() const override;

 private:
  std::shared_ptr<VertexBuffer> vertex_buffer_;
  std::shared_ptr<IndexBuffer> index_buffer_;
  const int total_stride_;
  unsigned int id_ = 0;
};

}  // namespace genesis