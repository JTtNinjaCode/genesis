#include "glfw_input.h"

#include <GLFW/glfw3.h>

#include "core/application.h"
namespace genesis {
GLFWInput::GLFWInput() {
  initializeKeycodeTable();
  initializeMouseButtonTable();
}

bool GLFWInput::IsKeyPressed(Keycode keycode) const {
  int glfw_keycode = GetGLFWKeycdodeFromGenesisKeycode(keycode);
  return (GLFW_PRESS ==
          glfwGetKey(static_cast<GLFWwindow*>(
                         Application::Get().GetWindow().GetNativeWindow()),
                     glfw_keycode));
}

float GLFWInput::GetMouseButton(MouseButton button) const {
  int glfw_button = GetGLFWMouseButtonFromGenesisMouseButton(button);
  return (
      GLFW_PRESS ==
      glfwGetMouseButton(static_cast<GLFWwindow*>(
                             Application::Get().GetWindow().GetNativeWindow()),
                         glfw_button));
}

std::pair<float, float> GLFWInput::GetMousePosition() const {
  double xpos, ypos;
  glfwGetCursorPos(static_cast<GLFWwindow*>(
                       Application::Get().GetWindow().GetNativeWindow()),
                   &xpos, &ypos);
  return {xpos, ypos};
}

float GLFWInput::GetMousePositionX() const {
  double xpos;
  glfwGetCursorPos(static_cast<GLFWwindow*>(
                       Application::Get().GetWindow().GetNativeWindow()),
                   &xpos, nullptr);
  return xpos;
}

float GLFWInput::GetMousePositionY() const {
  double ypos;
  glfwGetCursorPos(static_cast<GLFWwindow*>(
                       Application::Get().GetWindow().GetNativeWindow()),
                   nullptr, &ypos);
  return ypos;
}

Keycode GLFWInput::GetGenesisKeycodeFromGLFWKeycode(int keycode) const {
  const auto iter = lookup_genesis_keycode_table.find(keycode);
  if (iter == lookup_genesis_keycode_table.cend()) {
    return Keycode::kKeyUnknown;
  }
  return iter->second;
}

int GLFWInput::GetGLFWKeycdodeFromGenesisKeycode(Keycode keycode) const {
  const auto iter = lookup_glfw_keycode_table.find(keycode);
  if (iter == lookup_glfw_keycode_table.cend()) {
    return GLFW_KEY_UNKNOWN;
  }
  return iter->second;
}

MouseButton GLFWInput::GetGenesisMouseButtonFromGLFWMouseButton(
    int button) const {
  const auto iter = lookup_genesis_mouse_button_table.find(button);
  if (iter == lookup_genesis_mouse_button_table.cend()) {
    return MouseButton::kButton1;
  }
  return iter->second;
}

int GLFWInput::GetGLFWMouseButtonFromGenesisMouseButton(
    MouseButton button) const {
  const auto iter = lookup_glfw_mouse_button_table.find(button);
  if (iter == lookup_glfw_mouse_button_table.cend()) {
    return -1;  // GLFW_BUTTON_UNKNOWN not exist.
  }
  return iter->second;
}

void GLFWInput::initializeKeycodeTable() {
  // initialize genesis keycode table
  lookup_genesis_keycode_table[GLFW_KEY_0] = Keycode::kKey0;
  lookup_genesis_keycode_table[GLFW_KEY_1] = Keycode::kKey1;
  lookup_genesis_keycode_table[GLFW_KEY_2] = Keycode::kKey2;
  lookup_genesis_keycode_table[GLFW_KEY_3] = Keycode::kKey3;
  lookup_genesis_keycode_table[GLFW_KEY_4] = Keycode::kKey4;
  lookup_genesis_keycode_table[GLFW_KEY_5] = Keycode::kKey5;
  lookup_genesis_keycode_table[GLFW_KEY_6] = Keycode::kKey6;
  lookup_genesis_keycode_table[GLFW_KEY_7] = Keycode::kKey7;
  lookup_genesis_keycode_table[GLFW_KEY_8] = Keycode::kKey8;
  lookup_genesis_keycode_table[GLFW_KEY_9] = Keycode::kKey9;
  lookup_genesis_keycode_table[GLFW_KEY_A] = Keycode::kKeyA;
  lookup_genesis_keycode_table[GLFW_KEY_B] = Keycode::kKeyB;
  lookup_genesis_keycode_table[GLFW_KEY_C] = Keycode::kKeyC;
  lookup_genesis_keycode_table[GLFW_KEY_D] = Keycode::kKeyD;
  lookup_genesis_keycode_table[GLFW_KEY_E] = Keycode::kKeyE;
  lookup_genesis_keycode_table[GLFW_KEY_F] = Keycode::kKeyF;
  lookup_genesis_keycode_table[GLFW_KEY_G] = Keycode::kKeyG;
  lookup_genesis_keycode_table[GLFW_KEY_H] = Keycode::kKeyH;
  lookup_genesis_keycode_table[GLFW_KEY_I] = Keycode::kKeyI;
  lookup_genesis_keycode_table[GLFW_KEY_J] = Keycode::kKeyJ;
  lookup_genesis_keycode_table[GLFW_KEY_K] = Keycode::kKeyK;
  lookup_genesis_keycode_table[GLFW_KEY_L] = Keycode::kKeyL;
  lookup_genesis_keycode_table[GLFW_KEY_M] = Keycode::kKeyM;
  lookup_genesis_keycode_table[GLFW_KEY_O] = Keycode::kKeyO;
  lookup_genesis_keycode_table[GLFW_KEY_P] = Keycode::kKeyP;
  lookup_genesis_keycode_table[GLFW_KEY_Q] = Keycode::kKeyQ;
  lookup_genesis_keycode_table[GLFW_KEY_R] = Keycode::kKeyR;
  lookup_genesis_keycode_table[GLFW_KEY_S] = Keycode::kKeyS;
  lookup_genesis_keycode_table[GLFW_KEY_T] = Keycode::kKeyT;
  lookup_genesis_keycode_table[GLFW_KEY_U] = Keycode::kKeyU;
  lookup_genesis_keycode_table[GLFW_KEY_V] = Keycode::kKeyV;
  lookup_genesis_keycode_table[GLFW_KEY_W] = Keycode::kKeyW;
  lookup_genesis_keycode_table[GLFW_KEY_X] = Keycode::kKeyX;
  lookup_genesis_keycode_table[GLFW_KEY_Y] = Keycode::kKeyY;
  lookup_genesis_keycode_table[GLFW_KEY_Z] = Keycode::kKeyZ;
  lookup_genesis_keycode_table[GLFW_KEY_LEFT_BRACKET] =
      Keycode::kKeyLeftBracket;
  lookup_genesis_keycode_table[GLFW_KEY_RIGHT_BRACKET] =
      Keycode::kKeyRirghtBracket;
  lookup_genesis_keycode_table[GLFW_KEY_BACKSLASH] = Keycode::kKeyBackSlash;
  lookup_genesis_keycode_table[GLFW_KEY_SEMICOLON] = Keycode::kKeySemicolon;
  lookup_genesis_keycode_table[GLFW_KEY_EQUAL] = Keycode::kKeyEqual;
  lookup_genesis_keycode_table[GLFW_KEY_SPACE] = Keycode::kKeySpace;
  lookup_genesis_keycode_table[GLFW_KEY_APOSTROPHE] = Keycode::kKeyApostrophe;
  lookup_genesis_keycode_table[GLFW_KEY_COMMA] = Keycode::kKeyComma;
  lookup_genesis_keycode_table[GLFW_KEY_MINUS] = Keycode::kKeyMinus;
  lookup_genesis_keycode_table[GLFW_KEY_PERIOD] = Keycode::kKeyPeriod;
  lookup_genesis_keycode_table[GLFW_KEY_SLASH] = Keycode::kKeySlash;
  lookup_genesis_keycode_table[GLFW_KEY_GRAVE_ACCENT] =
      Keycode::kKeyGraveAccent;
  lookup_genesis_keycode_table[GLFW_KEY_KP_0] = Keycode::kKeyPad0;
  lookup_genesis_keycode_table[GLFW_KEY_KP_1] = Keycode::kKeyPad1;
  lookup_genesis_keycode_table[GLFW_KEY_KP_2] = Keycode::kKeyPad2;
  lookup_genesis_keycode_table[GLFW_KEY_KP_3] = Keycode::kKeyPad3;
  lookup_genesis_keycode_table[GLFW_KEY_KP_4] = Keycode::kKeyPad4;
  lookup_genesis_keycode_table[GLFW_KEY_KP_5] = Keycode::kKeyPad5;
  lookup_genesis_keycode_table[GLFW_KEY_KP_6] = Keycode::kKeyPad6;
  lookup_genesis_keycode_table[GLFW_KEY_KP_7] = Keycode::kKeyPad7;
  lookup_genesis_keycode_table[GLFW_KEY_KP_8] = Keycode::kKeyPad8;
  lookup_genesis_keycode_table[GLFW_KEY_KP_9] = Keycode::kKeyPad9;
  lookup_genesis_keycode_table[GLFW_KEY_F1] = Keycode::kKeyF1;
  lookup_genesis_keycode_table[GLFW_KEY_F2] = Keycode::kKeyF2;
  lookup_genesis_keycode_table[GLFW_KEY_F3] = Keycode::kKeyF3;
  lookup_genesis_keycode_table[GLFW_KEY_F4] = Keycode::kKeyF4;
  lookup_genesis_keycode_table[GLFW_KEY_F5] = Keycode::kKeyF5;
  lookup_genesis_keycode_table[GLFW_KEY_F6] = Keycode::kKeyF6;
  lookup_genesis_keycode_table[GLFW_KEY_F7] = Keycode::kKeyF7;
  lookup_genesis_keycode_table[GLFW_KEY_F8] = Keycode::kKeyF8;
  lookup_genesis_keycode_table[GLFW_KEY_F9] = Keycode::kKeyF9;
  lookup_genesis_keycode_table[GLFW_KEY_F10] = Keycode::kKeyF10;
  lookup_genesis_keycode_table[GLFW_KEY_F11] = Keycode::kKeyF11;
  lookup_genesis_keycode_table[GLFW_KEY_F12] = Keycode::kKeyF12;
  lookup_genesis_keycode_table[GLFW_KEY_ESCAPE] = Keycode::kKeyEscape;
  lookup_genesis_keycode_table[GLFW_KEY_BACKSPACE] = Keycode::kKeyBackspace;
  lookup_genesis_keycode_table[GLFW_KEY_CAPS_LOCK] = Keycode::kKeyCapsLock;
  lookup_genesis_keycode_table[GLFW_KEY_TAB] = Keycode::kKeyTab;
  lookup_genesis_keycode_table[GLFW_KEY_ENTER] = Keycode::kKeyEnter;
  lookup_genesis_keycode_table[GLFW_KEY_LEFT_SHIFT] = Keycode::kKeyLeftShift;
  lookup_genesis_keycode_table[GLFW_KEY_LEFT_CONTROL] =
      Keycode::kKeyLeftControl;
  lookup_genesis_keycode_table[GLFW_KEY_LEFT_ALT] = Keycode::kKeyLeftAlt;
  lookup_genesis_keycode_table[GLFW_KEY_LEFT_SUPER] = Keycode::kKeyLeftSuper;
  lookup_genesis_keycode_table[GLFW_KEY_RIGHT_SHIFT] = Keycode::kKeyRightShift;
  lookup_genesis_keycode_table[GLFW_KEY_RIGHT_CONTROL] =
      Keycode::kKeyRightControl;
  lookup_genesis_keycode_table[GLFW_KEY_RIGHT_ALT] = Keycode::kKeyRightAlt;
  lookup_genesis_keycode_table[GLFW_KEY_RIGHT_SUPER] = Keycode::kKeyRightSuper;
  lookup_genesis_keycode_table[GLFW_KEY_MENU] = Keycode::kKeyMenu;
  lookup_genesis_keycode_table[GLFW_KEY_INSERT] = Keycode::kKeyInsert;
  lookup_genesis_keycode_table[GLFW_KEY_DELETE] = Keycode::kKeyDelete;
  lookup_genesis_keycode_table[GLFW_KEY_HOME] = Keycode::kKeyHome;
  lookup_genesis_keycode_table[GLFW_KEY_END] = Keycode::kKeyEnd;
  lookup_genesis_keycode_table[GLFW_KEY_PAGE_UP] = Keycode::kKeyPageUp;
  lookup_genesis_keycode_table[GLFW_KEY_PAGE_DOWN] = Keycode::kKeyPageDown;
  lookup_genesis_keycode_table[GLFW_KEY_RIGHT] = Keycode::kKeyRight;
  lookup_genesis_keycode_table[GLFW_KEY_LEFT] = Keycode::kKeyLeft;
  lookup_genesis_keycode_table[GLFW_KEY_DOWN] = Keycode::kKeyDwon;
  lookup_genesis_keycode_table[GLFW_KEY_UP] = Keycode::kKeyUp;
  lookup_genesis_keycode_table[GLFW_KEY_SCROLL_LOCK] = Keycode::kKeyScrollLock;
  lookup_genesis_keycode_table[GLFW_KEY_PRINT_SCREEN] =
      Keycode::kKeyPrintScreen;
  lookup_genesis_keycode_table[GLFW_KEY_PAUSE] = Keycode::kKeyPause;
  lookup_genesis_keycode_table[GLFW_KEY_KP_DECIMAL] = Keycode::kKeyPadDecimal;
  lookup_genesis_keycode_table[GLFW_KEY_KP_DIVIDE] = Keycode::kKeyPadDivide;
  lookup_genesis_keycode_table[GLFW_KEY_KP_MULTIPLY] = Keycode::kKeyPadMultiply;
  lookup_genesis_keycode_table[GLFW_KEY_KP_SUBTRACT] = Keycode::kKeyPadSubtract;
  lookup_genesis_keycode_table[GLFW_KEY_KP_ADD] = Keycode::kKeyPadAdd;
  lookup_genesis_keycode_table[GLFW_KEY_KP_EQUAL] = Keycode::kKeyPadEqual;
  lookup_genesis_keycode_table[GLFW_KEY_KP_ENTER] = Keycode::kKeyPadEnter;
  lookup_genesis_keycode_table[GLFW_KEY_NUM_LOCK] = Keycode::kKeyNumLock;

  // initialize glfw keycode table
  lookup_glfw_keycode_table[Keycode::kKey0] = GLFW_KEY_0;
  lookup_glfw_keycode_table[Keycode::kKey1] = GLFW_KEY_1;
  lookup_glfw_keycode_table[Keycode::kKey2] = GLFW_KEY_2;
  lookup_glfw_keycode_table[Keycode::kKey3] = GLFW_KEY_3;
  lookup_glfw_keycode_table[Keycode::kKey4] = GLFW_KEY_4;
  lookup_glfw_keycode_table[Keycode::kKey5] = GLFW_KEY_5;
  lookup_glfw_keycode_table[Keycode::kKey6] = GLFW_KEY_6;
  lookup_glfw_keycode_table[Keycode::kKey7] = GLFW_KEY_7;
  lookup_glfw_keycode_table[Keycode::kKey8] = GLFW_KEY_8;
  lookup_glfw_keycode_table[Keycode::kKey9] = GLFW_KEY_9;
  lookup_glfw_keycode_table[Keycode::kKeyA] = GLFW_KEY_A;
  lookup_glfw_keycode_table[Keycode::kKeyB] = GLFW_KEY_B;
  lookup_glfw_keycode_table[Keycode::kKeyC] = GLFW_KEY_C;
  lookup_glfw_keycode_table[Keycode::kKeyD] = GLFW_KEY_D;
  lookup_glfw_keycode_table[Keycode::kKeyE] = GLFW_KEY_E;
  lookup_glfw_keycode_table[Keycode::kKeyF] = GLFW_KEY_F;
  lookup_glfw_keycode_table[Keycode::kKeyG] = GLFW_KEY_G;
  lookup_glfw_keycode_table[Keycode::kKeyH] = GLFW_KEY_H;
  lookup_glfw_keycode_table[Keycode::kKeyI] = GLFW_KEY_I;
  lookup_glfw_keycode_table[Keycode::kKeyJ] = GLFW_KEY_J;
  lookup_glfw_keycode_table[Keycode::kKeyK] = GLFW_KEY_K;
  lookup_glfw_keycode_table[Keycode::kKeyL] = GLFW_KEY_L;
  lookup_glfw_keycode_table[Keycode::kKeyM] = GLFW_KEY_M;
  lookup_glfw_keycode_table[Keycode::kKeyO] = GLFW_KEY_O;
  lookup_glfw_keycode_table[Keycode::kKeyP] = GLFW_KEY_P;
  lookup_glfw_keycode_table[Keycode::kKeyQ] = GLFW_KEY_Q;
  lookup_glfw_keycode_table[Keycode::kKeyR] = GLFW_KEY_R;
  lookup_glfw_keycode_table[Keycode::kKeyS] = GLFW_KEY_S;
  lookup_glfw_keycode_table[Keycode::kKeyT] = GLFW_KEY_T;
  lookup_glfw_keycode_table[Keycode::kKeyU] = GLFW_KEY_U;
  lookup_glfw_keycode_table[Keycode::kKeyV] = GLFW_KEY_V;
  lookup_glfw_keycode_table[Keycode::kKeyW] = GLFW_KEY_W;
  lookup_glfw_keycode_table[Keycode::kKeyX] = GLFW_KEY_X;
  lookup_glfw_keycode_table[Keycode::kKeyY] = GLFW_KEY_Y;
  lookup_glfw_keycode_table[Keycode::kKeyZ] = GLFW_KEY_Z;
  lookup_glfw_keycode_table[Keycode::kKeyLeftBracket] = GLFW_KEY_LEFT_BRACKET;
  lookup_glfw_keycode_table[Keycode::kKeyRirghtBracket] =
      GLFW_KEY_RIGHT_BRACKET;
  lookup_glfw_keycode_table[Keycode::kKeyBackSlash] = GLFW_KEY_BACKSLASH;
  lookup_glfw_keycode_table[Keycode::kKeySemicolon] = GLFW_KEY_SEMICOLON;
  lookup_glfw_keycode_table[Keycode::kKeyEqual] = GLFW_KEY_EQUAL;
  lookup_glfw_keycode_table[Keycode::kKeySpace] = GLFW_KEY_SPACE;
  lookup_glfw_keycode_table[Keycode::kKeyApostrophe] = GLFW_KEY_APOSTROPHE;
  lookup_glfw_keycode_table[Keycode::kKeyComma] = GLFW_KEY_COMMA;
  lookup_glfw_keycode_table[Keycode::kKeyMinus] = GLFW_KEY_MINUS;
  lookup_glfw_keycode_table[Keycode::kKeyPeriod] = GLFW_KEY_PERIOD;
  lookup_glfw_keycode_table[Keycode::kKeySlash] = GLFW_KEY_SLASH;
  lookup_glfw_keycode_table[Keycode::kKeyGraveAccent] = GLFW_KEY_GRAVE_ACCENT;
  lookup_glfw_keycode_table[Keycode::kKeyPad0] = GLFW_KEY_KP_0;
  lookup_glfw_keycode_table[Keycode::kKeyPad1] = GLFW_KEY_KP_1;
  lookup_glfw_keycode_table[Keycode::kKeyPad2] = GLFW_KEY_KP_2;
  lookup_glfw_keycode_table[Keycode::kKeyPad3] = GLFW_KEY_KP_3;
  lookup_glfw_keycode_table[Keycode::kKeyPad4] = GLFW_KEY_KP_4;
  lookup_glfw_keycode_table[Keycode::kKeyPad5] = GLFW_KEY_KP_5;
  lookup_glfw_keycode_table[Keycode::kKeyPad6] = GLFW_KEY_KP_6;
  lookup_glfw_keycode_table[Keycode::kKeyPad7] = GLFW_KEY_KP_7;
  lookup_glfw_keycode_table[Keycode::kKeyPad8] = GLFW_KEY_KP_8;
  lookup_glfw_keycode_table[Keycode::kKeyPad9] = GLFW_KEY_KP_9;
  lookup_glfw_keycode_table[Keycode::kKeyF1] = GLFW_KEY_F1;
  lookup_glfw_keycode_table[Keycode::kKeyF2] = GLFW_KEY_F2;
  lookup_glfw_keycode_table[Keycode::kKeyF3] = GLFW_KEY_F3;
  lookup_glfw_keycode_table[Keycode::kKeyF4] = GLFW_KEY_F4;
  lookup_glfw_keycode_table[Keycode::kKeyF5] = GLFW_KEY_F5;
  lookup_glfw_keycode_table[Keycode::kKeyF6] = GLFW_KEY_F6;
  lookup_glfw_keycode_table[Keycode::kKeyF7] = GLFW_KEY_F7;
  lookup_glfw_keycode_table[Keycode::kKeyF8] = GLFW_KEY_F8;
  lookup_glfw_keycode_table[Keycode::kKeyF9] = GLFW_KEY_F9;
  lookup_glfw_keycode_table[Keycode::kKeyF10] = GLFW_KEY_F10;
  lookup_glfw_keycode_table[Keycode::kKeyF11] = GLFW_KEY_F11;
  lookup_glfw_keycode_table[Keycode::kKeyF12] = GLFW_KEY_F12;
  lookup_glfw_keycode_table[Keycode::kKeyEscape] = GLFW_KEY_ESCAPE;
  lookup_glfw_keycode_table[Keycode::kKeyBackspace] = GLFW_KEY_BACKSPACE;
  lookup_glfw_keycode_table[Keycode::kKeyCapsLock] = GLFW_KEY_CAPS_LOCK;
  lookup_glfw_keycode_table[Keycode::kKeyTab] = GLFW_KEY_TAB;
  lookup_glfw_keycode_table[Keycode::kKeyEnter] = GLFW_KEY_ENTER;
  lookup_glfw_keycode_table[Keycode::kKeyLeftShift] = GLFW_KEY_LEFT_SHIFT;
  lookup_glfw_keycode_table[Keycode::kKeyLeftControl] = GLFW_KEY_LEFT_CONTROL;
  lookup_glfw_keycode_table[Keycode::kKeyLeftAlt] = GLFW_KEY_LEFT_ALT;
  lookup_glfw_keycode_table[Keycode::kKeyLeftSuper] = GLFW_KEY_LEFT_SUPER;
  lookup_glfw_keycode_table[Keycode::kKeyRightShift] = GLFW_KEY_RIGHT_SHIFT;
  lookup_glfw_keycode_table[Keycode::kKeyRightControl] = GLFW_KEY_RIGHT_CONTROL;
  lookup_glfw_keycode_table[Keycode::kKeyRightAlt] = GLFW_KEY_RIGHT_ALT;
  lookup_glfw_keycode_table[Keycode::kKeyRightSuper] = GLFW_KEY_RIGHT_SUPER;
  lookup_glfw_keycode_table[Keycode::kKeyMenu] = GLFW_KEY_MENU;
  lookup_glfw_keycode_table[Keycode::kKeyInsert] = GLFW_KEY_INSERT;
  lookup_glfw_keycode_table[Keycode::kKeyDelete] = GLFW_KEY_DELETE;
  lookup_glfw_keycode_table[Keycode::kKeyHome] = GLFW_KEY_HOME;
  lookup_glfw_keycode_table[Keycode::kKeyEnd] = GLFW_KEY_END;
  lookup_glfw_keycode_table[Keycode::kKeyPageUp] = GLFW_KEY_PAGE_UP;
  lookup_glfw_keycode_table[Keycode::kKeyPageDown] = GLFW_KEY_PAGE_DOWN;
  lookup_glfw_keycode_table[Keycode::kKeyRight] = GLFW_KEY_RIGHT;
  lookup_glfw_keycode_table[Keycode::kKeyLeft] = GLFW_KEY_LEFT;
  lookup_glfw_keycode_table[Keycode::kKeyDwon] = GLFW_KEY_DOWN;
  lookup_glfw_keycode_table[Keycode::kKeyUp] = GLFW_KEY_UP;
  lookup_glfw_keycode_table[Keycode::kKeyScrollLock] = GLFW_KEY_SCROLL_LOCK;
  lookup_glfw_keycode_table[Keycode::kKeyPrintScreen] = GLFW_KEY_PRINT_SCREEN;
  lookup_glfw_keycode_table[Keycode::kKeyPause] = GLFW_KEY_PAUSE;
  lookup_glfw_keycode_table[Keycode::kKeyPadDecimal] = GLFW_KEY_KP_DECIMAL;
  lookup_glfw_keycode_table[Keycode::kKeyPadDivide] = GLFW_KEY_KP_DIVIDE;
  lookup_glfw_keycode_table[Keycode::kKeyPadMultiply] = GLFW_KEY_KP_MULTIPLY;
  lookup_glfw_keycode_table[Keycode::kKeyPadSubtract] = GLFW_KEY_KP_SUBTRACT;
  lookup_glfw_keycode_table[Keycode::kKeyPadAdd] = GLFW_KEY_KP_ADD;
  lookup_glfw_keycode_table[Keycode::kKeyPadEqual] = GLFW_KEY_KP_EQUAL;
  lookup_glfw_keycode_table[Keycode::kKeyPadEnter] = GLFW_KEY_KP_ENTER;
  lookup_glfw_keycode_table[Keycode::kKeyNumLock] = GLFW_KEY_NUM_LOCK;
}
void GLFWInput::initializeMouseButtonTable() {
  // initialize glfw mouse button table
  lookup_glfw_mouse_button_table[MouseButton::kButton1] = GLFW_MOUSE_BUTTON_1;
  lookup_glfw_mouse_button_table[MouseButton::kButton2] = GLFW_MOUSE_BUTTON_2;
  lookup_glfw_mouse_button_table[MouseButton::kButton3] = GLFW_MOUSE_BUTTON_3;

  // initialized genesis mouse button table
  lookup_genesis_mouse_button_table[GLFW_MOUSE_BUTTON_1] =
      MouseButton::kButton1;
  lookup_genesis_mouse_button_table[GLFW_MOUSE_BUTTON_2] =
      MouseButton::kButton2;
  lookup_genesis_mouse_button_table[GLFW_MOUSE_BUTTON_3] =
      MouseButton::kButton3;
}
}  // namespace genesis
