#pragma once
#include <unordered_map>

#include "core/input/input.h"
namespace genesis {
class GLFWInput : public Input {
 public:
  GLFWInput();

  bool IsKeyPressed(Keycode keycode) const override;
  bool IsMousePressed(MouseButton mouse_button) const override;
  int GetMouseButton(MouseButton button) const override;
  glm::vec2 GetMousePosition() const override;
  std::string GetKeyCodeName(Keycode key) const override;

  Keycode GetGenesisKeycodeFromGLFWKeycode(int keycode) const;
  int GetGLFWKeycdodeFromGenesisKeycode(Keycode keycode) const;
  MouseButton GetGenesisMouseButtonFromGLFWMouseButton(int button) const;
  int GetGLFWMouseButtonFromGenesisMouseButton(MouseButton button) const;

 private:
  void InitializeKeycodeTable();
  void InitializeMouseButtonTable();

  std::unordered_map<int, Keycode> lookup_genesis_keycode_table;
  std::unordered_map<int, MouseButton> lookup_genesis_mouse_button_table;
  std::unordered_map<Keycode, int> lookup_glfw_keycode_table;
  std::unordered_map<MouseButton, int> lookup_glfw_mouse_button_table;
};
}  // namespace genesis