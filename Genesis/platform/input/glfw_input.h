#pragma once
#include "core/input.h"
namespace Genesis {
class GLFWInput : public Input {
  friend class Input;

 private:
  GLFWInput() {}
  bool IsKeyPressed(int key) const override;
  float GetMouseButton(int button) const override;
  std::pair<float, float> GetMousePosition() const override;
  float GetMousePositionX() const override;
  float GetMousePositionY() const override;
};
}  // namespace Genesis