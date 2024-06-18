#include "core/input/input.h"

#include "platform/input/glfw_input.h"
namespace genesis {
std::unique_ptr<Input> Input::instanced_ = nullptr;

Input& Input::GetInstance() {
  if (!instanced_) {
    instanced_ = std::make_unique<GLFWInput>();
  }
  return *instanced_;
};
}  // namespace genesis
