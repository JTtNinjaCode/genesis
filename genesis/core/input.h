#pragma once
#include <utility>
#include <string>
#include "core/core.h"
namespace genesis {
enum class Keycode;
enum class MouseButton;

// singleton
class DLL_API Input {
 public:
  virtual bool IsKeyPressed(Keycode key) const = 0;
  virtual std::string GetKeyCodeName(Keycode key) const = 0;
  virtual int GetMouseButton(MouseButton button) const = 0;
  virtual std::pair<double, double> GetMousePosition() const = 0;
  virtual double GetMousePositionX() const = 0;
  virtual double GetMousePositionY() const = 0;
  static Input& GetInstance();

 private:
  static Input* instanced_;
};

enum class Keycode {
  /* Printable Keys */
  kKey0,
  kKey1,
  kKey2,
  kKey3,
  kKey4,
  kKey5,
  kKey6,
  kKey7,
  kKey8,
  kKey9,

  kKeyA,
  kKeyB,
  kKeyC,
  kKeyD,
  kKeyE,
  kKeyF,
  kKeyG,
  kKeyH,
  kKeyI,
  kKeyJ,
  kKeyK,
  kKeyL,
  kKeyM,
  kKeyN,
  kKeyO,
  kKeyP,
  kKeyQ,
  kKeyR,
  kKeyS,
  kKeyT,
  kKeyU,
  kKeyV,
  kKeyW,
  kKeyX,
  kKeyY,
  kKeyZ,

  kKeyLeftBracket,   /* [ */
  kKeyRirghtBracket, /* ] */
  kKeyBackSlash,     /* \ */
  kKeySemicolon,     /* ; */
  kKeyEqual,         /* = */
  kKeySpace,         /*   */
  kKeyApostrophe,    /* ' */
  kKeyComma,         /* , */
  kKeyMinus,         /* - */
  kKeyPeriod,        /* . */
  kKeySlash,         /* / */
  kKeyGraveAccent,   /* ` */

  kKeyPad0,
  kKeyPad1,
  kKeyPad2,
  kKeyPad3,
  kKeyPad4,
  kKeyPad5,
  kKeyPad6,
  kKeyPad7,
  kKeyPad8,
  kKeyPad9,

  /* Function Keys */
  kKeyF1,
  kKeyF2,
  kKeyF3,
  kKeyF4,
  kKeyF5,
  kKeyF6,
  kKeyF7,
  kKeyF8,
  kKeyF9,
  kKeyF10,
  kKeyF11,
  kKeyF12,

  kKeyEscape,
  kKeyBackspace,
  kKeyCapsLock,
  kKeyTab,
  kKeyEnter,
  kKeyLeftShift,
  kKeyLeftControl,
  kKeyLeftAlt,
  kKeyLeftSuper,
  kKeyRightShift,
  kKeyRightControl,
  kKeyRightAlt,
  kKeyRightSuper,
  kKeyMenu,

  kKeyInsert,
  kKeyDelete,
  kKeyHome,
  kKeyEnd,
  kKeyPageUp,
  kKeyPageDown,

  kKeyRight,
  kKeyLeft,
  kKeyDwon,
  kKeyUp,

  kKeyScrollLock,
  kKeyPrintScreen,
  kKeyPause,

  /* KeyPad, Printable Keys*/
  kKeyPadDecimal,  /* . */
  kKeyPadDivide,   /* / */
  kKeyPadMultiply, /* * */
  kKeyPadSubtract, /* - */
  kKeyPadAdd,      /* + */
  kKeyPadEqual,    /* = */

  /* Keypad, Function Keys */
  kKeyNumLock,
  kKeyPadEnter,

  /* Unknown */
  kKeyUnknown
};

enum class MouseButton {
  kButton1,
  kButton2,
  kButton3,
  kButton4,
  kButton5,
  kButton6,
  kButton7,
  kButton8,
  // Assign Left Button Must be kButton1
  kButtonLeft = kButton1,
  // Assign Middle Button Must be kButton2
  kButtonMiddle = kButton2,
  // Assign Right Button Must be kButton3
  kButtonRight = kButton3,

  /* Unknown */
  kButtonUnknown
};
}  // namespace genesis