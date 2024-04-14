#pragma once

#include "../System.hh"
#include "OpenGLViewer.hh"
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>

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
