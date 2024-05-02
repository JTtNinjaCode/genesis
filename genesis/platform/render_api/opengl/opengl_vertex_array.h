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

  void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertex_buffer) override;
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer> index_buffer) override;

 private:
  std::shared_ptr<VertexBuffer> vbo_;
  std::shared_ptr<IndexBuffer> ibo_;
  const int total_stride_;
  unsigned int id_ = 0;
};

}  // namespace genesis