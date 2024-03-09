#pragma once
#include <glad/glad.h>

#include <vector>

#include "core/renderer/buffer_layout.h"
#include "core/renderer/vertex_array.h"
namespace genesis {
GLenum MathDataTypeToOpenGLBaseType(MathDataType type);

class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray(const BufferLayout& buffer_layout);
  virtual ~OpenGLVertexArray();
  void Bind() const override;
  void Unbind() const override;
  void AddVertexBuffer(const VertexBuffer& vertex_buffer) override;
  void SetIndexBuffer(const IndexBuffer& index_buffer) override;

 private:
  unsigned int id_ = 0;
};

}  // namespace genesis