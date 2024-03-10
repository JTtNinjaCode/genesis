#include "opengl_vertex_array.h"

#include <glad/glad.h>

#include "core/log.h"
namespace genesis {

GLenum MathDataTypeToOpenGLBaseType(MathDataType type) {
  switch (type) {
    case MathDataType::kFloat3:
      return GL_FLOAT;
    case MathDataType::kFloat4:
      return GL_FLOAT;
    case MathDataType::kMat3:
      return GL_FLOAT;
    case MathDataType::kMat4:
      return GL_FLOAT;
  }
  CORE_ASSERT(false, "Unknown MathDataType!");
  return 0;
}

OpenGLVertexArray::OpenGLVertexArray(const BufferLayout& buffer_layout) {
  glCreateVertexArrays(1, &id_);

  glBindVertexArray(id_);
  CORE_ASSERT(!buffer_layout.GetLayout().empty(), "buffer_layout is empty");
  int index = 0;
  size_t offset = 0;
  for (const auto& element : buffer_layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, element.count,
                          MathDataTypeToOpenGLBaseType(element.type), GL_FALSE,
                          buffer_layout.GetTotalStride(), (const void*)offset);
    offset += element.size;
    index++;
  }
}

OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &id_); }

void OpenGLVertexArray::Bind() const { glBindVertexArray(id_); }

void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::AddVertexBuffer(const VertexBuffer& vertex_buffer) {
  glBindVertexArray(id_);
  vertex_buffer.Bind();
}

void OpenGLVertexArray::SetIndexBuffer(const IndexBuffer& index_buffer) {
  glBindVertexArray(id_);
  index_buffer.Bind();
  count_ = index_buffer.GetCount();
  has_index_ = true;
}
}  // namespace genesis
