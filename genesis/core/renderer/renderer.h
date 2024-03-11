#pragma once
#include <memory>

#include "core/renderer/renderer_api.h"
#include "core/renderer/vertex_array.h"
namespace genesis {
class Renderer {
 public:
  void BeginScene() ;
  void EndScene();
  void Submit(const VertexArray& vertex_array);
};
}  // namespace genesis
