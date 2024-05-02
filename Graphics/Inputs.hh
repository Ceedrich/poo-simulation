#pragma once
#include <QKeyEvent>

namespace FLAGS {
enum FLAGS {
  STRAVE_FORWARD = 1 << 0,
  STRAVE_BACKWARD = 1 << 1,
  STRAVE_UP = 1 << 2,
  STRAVE_DOWN = 1 << 3,
  STRAVE_LEFT = 1 << 4,
  STRAVE_RIGHT = 1 << 5,

  ROTATE_RIGHT = 1 << 6,
  ROTATE_LEFT = 1 << 7,
  ROTATE_UP = 1 << 8,
  ROTATE_DOWN = 1 << 9,
};
}

namespace Inputs {
enum STRAVE_KEY {
  STRAVE_FORWARD = Qt::Key::Key_W,
  STRAVE_BACKWARD = Qt::Key::Key_S,
  STRAVE_LEFT = Qt::Key::Key_A,
  STRAVE_RIGHT = Qt::Key::Key_D,
  STRAVE_UP = Qt::Key::Key_Space,
  STRAVE_DOWN = Qt::Key::Key_Shift,
};

enum ROTATE_KEY {
  ROTATE_UP = Qt::Key::Key_Up,
  ROTATE_DOWN = Qt::Key::Key_Down,
  ROTATE_LEFT = Qt::Key::Key_Left,
  ROTATE_RIGHT = Qt::Key::Key_Right,
};

enum CONTROL_KEY {
  QUIT = Qt::Key::Key_Q,
  PAUSE = Qt::Key::Key_Escape,
  SPEED_MODIFIER = Qt::Key::Key_Control,
  EVOLVE = Qt::Key::Key_Return,
  MOVE_LIGHT_SOURCE = Qt::Key::Key_L,
  TOGGLE_AMBIENT = Qt::Key::Key_7,
  TOGGLE_DIFFUSE = Qt::Key::Key_8,
  TOGGLE_SPECULAR = Qt::Key::Key_9,
};
} // namespace Inputs
