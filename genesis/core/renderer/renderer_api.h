#pragma once
#include "core/renderer/vertex_array.h"
namespace genesis {
class RendererAPI {
 public:
  enum class API { None, OpenGL };
  static API GetAPI() { return api_; }

 private:
  static API api_;
};
}  // namespace genesis
