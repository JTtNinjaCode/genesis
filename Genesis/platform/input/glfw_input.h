#pragma once
#include <unordered_map>
#include <utility>

#include "core/input.h"
namespace Genesis {
class GLFWInput : public Input {
  friend class Input;

 private:
  GLFWInput();

  bool IsKeyPressed(Keycode keycode) const override;
  float GetMouseButton(MouseButton button) const override;
  std::pair<float, float> GetMousePosition() const override;
  float GetMousePositionX() const override;
  float GetMousePositionY() const override;

  void initializeKeycodeTable();
  void initializeMouseButtonTable();

  Keycode GetGenesisKeycodeFromGLFWKeycode(int keycode) const;
  int GetGLFWKeycdodeFromGenesisKeycode(Keycode keycode) const;
  MouseButton GetGenesisMouseButtonFromGLFWMouseButton(int button) const;
  int GetGLFWMouseButtonFromGenesisMouseButton(MouseButton button) const;

  std::unordered_map<int, Keycode> lookup_genesis_keycode_table;
  std::unordered_map<int, MouseButton> lookup_genesis_mouse_button_table;
  std::unordered_map<Keycode, int> lookup_glfw_keycode_table;
  std::unordered_map<MouseButton, int> lookup_glfw_mouse_button_table;
};
}  // namespace Genesis