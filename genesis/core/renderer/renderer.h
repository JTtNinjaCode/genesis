#pragma once
namespace genesis {
enum class RenderAPI { None, OpenGL };
class Renderer {
 public:
  static RenderAPI GetAPI();
 private:
  static RenderAPI api_;
};
}  // namespace genesis
