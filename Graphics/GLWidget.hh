#pragma once

#include "../System.hh"
#include "OpenGLViewer.hh"
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>

enum KEYMAP {
  // Movement
  KEY_UP = Qt::Key::Key_Space,
  KEY_DOWN = Qt::Key::Key_Shift,
  KEY_LEFT = Qt::Key::Key_A,
  KEY_RIGHT = Qt::Key::Key_D,
  KEY_FORWARD = Qt::Key::Key_W,
  KEY_BACKWARD = Qt::Key::Key_S,

  // Controls
  KEY_QUIT = Qt::Key::Key_Q,
  KEY_PAUSE = Qt::Key::Key_Escape,
};

class GLWidget : public QOpenGLWidget {
public:
  GLWidget(QWidget *parent = nullptr, System &&s = System::prefilled())
      : QOpenGLWidget(parent), system(std::move(s)) {}
  GLWidget(System &&s) : QOpenGLWidget(nullptr), system(std::move(s)) {}
  virtual ~GLWidget() = default;

private:
  virtual void initializeGL() override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL() override;

  // Events
  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void timerEvent(QTimerEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;

  void pause();

  int timerID;
  QElapsedTimer stopwatch;

  QPoint lastMousePosition;

  OpenGLViewer viewer;
  System system = System::prefilled();
};
