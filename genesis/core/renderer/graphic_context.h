#pragma once
namespace genesis {
class GraphicContext {
 public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};

}  // namespace genesis