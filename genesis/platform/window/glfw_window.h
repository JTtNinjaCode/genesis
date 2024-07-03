#pragma once
#pragma warning(push)
#pragma warning(disable : 4005)
#include <GLFW/glfw3.h>
#pragma warning(pop)
#include <string>

#include "core/renderer/graphic_context.h"
#include "core/window.h"
namespace genesis {

class DLL_API GLFWWindow : public Window {
 public:
  GLFWWindow(const std::string& title, unsigned int width, unsigned height);
  ~GLFWWindow();

  void OnUpdate() override;
  unsigned int GetWidth() const override;
  unsigned int GetHeight() const override;
  void SetCursorMode(const CursorMode cursor_mode) override;
  void SetVSync(bool open) override;
  bool IsVSync() const override;
  void* GetNativeWindow() override;
  void SetEventListener(const EventCallbackFunc& event_listener) override { data_.event_listener_ = event_listener; }

 private:
  static bool is_glfw_initialized_;

  GLFWwindow* window_;
  GraphicContext* context_;

  struct WindowData {
    bool is_vsync_ = false;
    EventCallbackFunc event_listener_;
  } data_;
};
}  // namespace genesis
