#pragma once
#include <GLFW/glfw3.h>

#include <string>

#include "core/window.h"
namespace Genesis {
class DLL_API GLFWWindow : public Window {
 public:
  GLFWWindow(const std::string& title, unsigned int width, unsigned height);
  ~GLFWWindow();

  void OnUpdate() override;
  unsigned int GetWidth() const override;
  unsigned int GetHeight() const override;
  void SetVSync(bool open) override;
  bool IsVSync() const override;

  void SetEventListener(const EventCallbackFunc& event_listener) override {
    data_.event_listener_ = event_listener;
  }

 private:
  static bool is_glfw_initialized_;

  ::GLFWwindow* window_;

  struct WindowData {
    bool is_vsync;
    EventCallbackFunc event_listener_;
  };

  WindowData data_;
};
}  // namespace Genesis
