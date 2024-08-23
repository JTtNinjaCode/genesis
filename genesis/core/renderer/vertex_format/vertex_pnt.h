#pragma once
#include <glm/glm.hpp>

#include "core/renderer/buffer_layout.h"
namespace genesis {
struct VertexPNT {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex_coord;
  static BufferLayout GetLayout() {
    return {{MathDataType::kFloat3, 0}, {MathDataType::kFloat3, 1}, {MathDataType::kFloat2, 2}};
  }
};

struct VertexPC {
  glm::vec3 position;
  glm::vec4 colors;
  static BufferLayout GetLayout() { return {{MathDataType::kFloat3, 0}, {MathDataType::kFloat4, 3}}; }
};
}  // namespace genesis