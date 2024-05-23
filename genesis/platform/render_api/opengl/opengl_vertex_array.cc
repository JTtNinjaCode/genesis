#include "opengl_vertex_array.h"

#include <glad/glad.h>

#include "core/log/log.h"
namespace genesis {

GLenum MathDataTypeToOpenGLBaseType(MathDataType type) {
  switch (type) {
    case MathDataType::kFloat2:
      return GL_FLOAT;
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

OpenGLVertexArray::OpenGLVertexArray(const BufferLayout& buffer_layout)
    : total_stride_(buffer_layout.GetTotalStride()) {
  CORE_ASSERT(!buffer_layout.GetLayout().empty(), "Buffer layout is empty.");
  glCreateVertexArrays(1, &id_);
  int index = 0;
  size_t offset = 0;
  for (const auto& element : buffer_layout) {
    glEnableVertexArrayAttrib(id_, index);
    glVertexArrayAttribBinding(id_, index, 0);
    glVertexArrayAttribFormat(id_, index, element.count, MathDataTypeToOpenGLBaseType(element.type), GL_FALSE, offset);
    offset += element.size;
    index++;
  }
}

OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &id_); }

void OpenGLVertexArray::Bind() const { glBindVertexArray(id_); }

void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

unsigned int OpenGLVertexArray::GetIndexCount() const { return index_buffer_->GetCount(); }

unsigned int OpenGLVertexArray::GetVertexCount() const { return vertex_buffer_->GetSize() / total_stride_; }

void OpenGLVertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer> vertex_buffer) {
  glVertexArrayVertexBuffer(id_, 0, vertex_buffer->GetId(), 0, total_stride_);
  vertex_buffer_ = vertex_buffer;
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> index_buffer) {
  glVertexArrayElementBuffer(id_, index_buffer->GetId());
  has_index_ = true;
  index_buffer_ = index_buffer;
}
VertexBuffer& OpenGLVertexArray::GetVertexBuffer() const { return *vertex_buffer_; }
IndexBuffer& OpenGLVertexArray::GetIndexBuffer() const { return *index_buffer_; }
}  // namespace genesis
