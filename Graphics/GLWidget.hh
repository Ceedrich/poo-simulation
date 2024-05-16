#pragma once

#include "../System.hh"
#include "OpenGLViewer.hh"
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>

class GLWidget : public QOpenGLWidget {
public:
  GLWidget(QWidget *parent = nullptr, System &&s = System::prefilled())
      : QOpenGLWidget(parent), system(std::move(s)),
        cMovementSpeed(
            std::max({system.enclosure().width(), system.enclosure().height(),
                      system.enclosure().length()}) /
            2.0) {
    setFocusPolicy(Qt::StrongFocus);
  }
  GLWidget(System &&s) : QOpenGLWidget(nullptr), system(std::move(s)) {
    setFocusPolicy(Qt::StrongFocus);
  }
  virtual ~GLWidget() = default;

  void setGraphicsLevel(OpenGLViewer::GRAPHICS_LEVEL level) {
    viewer.setGraphicsLevel(level);
  }

  void reset();
  void setCameraMovementSpeed(double v) { cMovementSpeed = v; }

private:
  virtual void initializeGL() override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL() override;

  void initCamera();
  void initLight();
  void saveToFile() const;
  void loadFromFile();

  // Events
  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void keyReleaseEvent(QKeyEvent *event) override;
  virtual void timerEvent(QTimerEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;

  void updateSystemTimer();
  void updateCameraTimer();

  void pause();

  OpenGLViewer viewer;
  System system = System::prefilled();

  int timerID;
  int ctimerID;
  unsigned short int keys_pressed = 0;
  double cMovementSpeed = 6.0;
  static constexpr double cSpeedMultiplier = 2.0;
  static constexpr double dt = 0.1;
  bool cSpeedUp = false;
  QElapsedTimer stopwatch, cstopwatch;

  QPoint lastMousePosition;
};
