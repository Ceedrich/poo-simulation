#pragma once
#include <QKeyEvent>

namespace Inputs {
enum STRAVE_KEY {
  FORWARD = Qt::Key::Key_W,
  BACKWARD = Qt::Key::Key_S,
  LEFT = Qt::Key::Key_A,
  RIGHT = Qt::Key::Key_D,
  UP = Qt::Key::Key_Space,
  DOWN = Qt::Key::Key_Shift,
};

enum CONTROL_KEY {
  QUIT = Qt::Key::Key_Q,
  PAUSE = Qt::Key::Key_Escape,
};
} // namespace Inputs
