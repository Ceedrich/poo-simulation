#pragma once

#include "../FileSaver/FileSaver.hh"
#include "../System.hh"
#include "OpenGLViewer.hh"
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>

class GLWidget : public QOpenGLWidget {
public:
  /**
   * @brief Constructor of the class GLWidget.
   * @param Parent widget
   * @param System
   */
  GLWidget(QWidget *parent = nullptr, System &&s = System::prefilled())
      : QOpenGLWidget(parent), system(std::move(s)),
        cMovementSpeed(
            std::max({system.enclosure().width(), system.enclosure().height(),
                      system.enclosure().length()}) /
            2.0) {
    setFocusPolicy(Qt::StrongFocus);
  }

  /**
   * @brief Constructor of the class GLWidget.
   * @param System
   */
  GLWidget(System &&s) : QOpenGLWidget(nullptr), system(std::move(s)) {
    setFocusPolicy(Qt::StrongFocus);
  }
  virtual ~GLWidget() = default;

  /**
   * @brief sets the graphics Level.
   * @param Level that the graphic level is set to.
   */
  void setGraphicsLevel(OpenGLViewer::GRAPHICS_LEVEL level) {
    viewer.setGraphicsLevel(level);
  }
  /**
   * @brief Resets the widget to initial status.
   */
  void reset();
  System::Info systemInfo() const;

private:
  bool slowDown = false;
  virtual void initializeGL() override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL() override;

  void initCamera();
  void initLight();
  void saveToFile();
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
  unsigned short int keysPressed = 0;
  double cMovementSpeed = 6.0;
  static constexpr double cSpeedMultiplier = 2.0;
  static constexpr double dt = 0.1;
  static constexpr double slowDownMultiplier = 0.2;
  QElapsedTimer stopwatch, cstopwatch;

  QPoint lastMousePosition;
};
