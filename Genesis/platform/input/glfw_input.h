#pragma once
#include <unordered_map>
#include <utility>

#include "core/input.h"
namespace genesis {
class GLFWInput : public Input {
  friend class Input;

 public:
  Keycode GetGenesisKeycodeFromGLFWKeycode(int keycode) const;
  int GetGLFWKeycdodeFromGenesisKeycode(Keycode keycode) const;
  MouseButton GetGenesisMouseButtonFromGLFWMouseButton(int button) const;
  int GetGLFWMouseButtonFromGenesisMouseButton(MouseButton button) const;

  bool IsKeyPressed(Keycode keycode) const override;
  int GetMouseButton(MouseButton button) const override;
  std::pair<double, double> GetMousePosition() const override;
  double GetMousePositionX() const override;
  double GetMousePositionY() const override;

 private:
  GLFWInput();

  void initializeKeycodeTable();
  void initializeMouseButtonTable();

  std::unordered_map<int, Keycode> lookup_genesis_keycode_table;
  std::unordered_map<int, MouseButton> lookup_genesis_mouse_button_table;
  std::unordered_map<Keycode, int> lookup_glfw_keycode_table;
  std::unordered_map<MouseButton, int> lookup_glfw_mouse_button_table;
};
}  // namespace genesis