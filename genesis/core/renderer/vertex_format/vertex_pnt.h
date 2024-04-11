#pragma once
#include <glm/glm.hpp>

#include "core/renderer/buffer_layout.h"
namespace genesis {
struct VertexPNT {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex_coord;
  static BufferLayout GetLayout();
};
}  // namespace genesis