#include "input.h"

#include "platform/input/glfw_input.h"
namespace Genesis {
Input* Input::instanced_ = nullptr;

Input& Input::GetInstance() {
  if (!instanced_) {
    instanced_ = new GLFWInput();
  }
  return *instanced_;
};
}  // namespace Genesis
