#include "vertex_pnt.h"

#include "core/renderer/buffer_layout.h"
namespace genesis {
BufferLayout VertexPNT::GetLayout() {
  return {MathDataType::kFloat3, MathDataType::kFloat3, MathDataType::kFloat2};
}

}  // namespace genesis