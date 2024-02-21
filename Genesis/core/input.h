#pragma once
#include <utility>
// singleton
namespace Genesis {

class Input {
 public:
  virtual bool IsKeyPressed(int key) const = 0;
  virtual float GetMouseButton(int button) const = 0;
  virtual std::pair<float, float> GetMousePosition() const = 0;
  virtual float GetMousePositionX() const = 0;
  virtual float GetMousePositionY() const = 0;
  static Input& GetInstance();

 protected:
  Input() {}

 private:
  static Input* instanced_;
};
}  // namespace Genesis