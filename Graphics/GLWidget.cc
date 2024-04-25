#include "GLWidget.hh"
#include "Inputs.hh"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTimerEvent>
#include <cmath>

using std::asin, std::clamp;

void GLWidget::initializeGL() {
  viewer.init();
  viewer.camera().move(10, 10, -10);
  timerID = startTimer(20);
  ctimerID = startTimer(20);
  pause();
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);

  QMatrix4x4 matrix;
  matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3,
                     1e5);
  viewer.setProjection(matrix);
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  system.draw_on(viewer);
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Inputs::ROTATE_LEFT:
    keys_pressed |= FLAGS::ROTATE_LEFT;
    break;
  case Inputs::ROTATE_RIGHT:
    keys_pressed |= FLAGS::ROTATE_RIGHT;
    break;
  case Inputs::ROTATE_UP:
    keys_pressed |= FLAGS::ROTATE_UP;
    break;
  case Inputs::ROTATE_DOWN:
    keys_pressed |= FLAGS::ROTATE_DOWN;
    break;
  case Inputs::STRAVE_FORWARD:
    keys_pressed |= FLAGS::STRAVE_FORWARD;
    break;
  case Inputs::STRAVE_BACKWARD:
    keys_pressed |= FLAGS::STRAVE_BACKWARD;
    break;
  case Inputs::STRAVE_LEFT:
    keys_pressed |= FLAGS::STRAVE_LEFT;
    break;
  case Inputs::STRAVE_RIGHT:
    keys_pressed |= FLAGS::STRAVE_RIGHT;
    break;
  case Inputs::STRAVE_DOWN:
    keys_pressed |= FLAGS::STRAVE_DOWN;
    break;
  case Inputs::STRAVE_UP:
    keys_pressed |= FLAGS::STRAVE_UP;
    break;
  case Inputs::PAUSE:
    pause();
    break;
  case Inputs::QUIT:
    close();
    break;
  }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Inputs::ROTATE_LEFT:
    keys_pressed &= ~FLAGS::ROTATE_LEFT;
    break;
  case Inputs::ROTATE_RIGHT:
    keys_pressed &= ~FLAGS::ROTATE_RIGHT;
    break;
  case Inputs::ROTATE_UP:
    keys_pressed &= ~FLAGS::ROTATE_UP;
    break;
  case Inputs::ROTATE_DOWN:
    keys_pressed &= ~FLAGS::ROTATE_DOWN;
    break;
  case Inputs::STRAVE_FORWARD:
    keys_pressed &= ~FLAGS::STRAVE_FORWARD;
    break;
  case Inputs::STRAVE_BACKWARD:
    keys_pressed &= ~FLAGS::STRAVE_BACKWARD;
    break;
  case Inputs::STRAVE_LEFT:
    keys_pressed &= ~FLAGS::STRAVE_LEFT;
    break;
  case Inputs::STRAVE_RIGHT:
    keys_pressed &= ~FLAGS::STRAVE_RIGHT;
    break;
  case Inputs::STRAVE_DOWN:
    keys_pressed &= ~FLAGS::STRAVE_DOWN;
    break;
  case Inputs::STRAVE_UP:
    keys_pressed &= ~FLAGS::STRAVE_UP;
    break;
  }
}

void GLWidget::timerEvent(QTimerEvent *event) {
  if (event->timerId() == timerID) {
    updateSystemTimer();
  }
  if (event->timerId() == ctimerID) {
    updateCameraTimer();
  }
  update();
}

void GLWidget::updateSystemTimer() {
  double dt = stopwatch.restart() / 1000.0;

  system.evolve(dt);
}
void GLWidget::updateCameraTimer() {
  constexpr double straveSpeed(6.0);
  constexpr double panSpeed(0.6);
  double dt = cstopwatch.restart() / 1000.0;
  if (!keys_pressed) {
    return;
  }

  if (keys_pressed & FLAGS::ROTATE_LEFT)
    viewer.camera().rotateYaw(+panSpeed * dt);
  if (keys_pressed & FLAGS::ROTATE_RIGHT)
    viewer.camera().rotateYaw(-panSpeed * dt);
  if (keys_pressed & FLAGS::ROTATE_UP)
    viewer.camera().rotatePitch(+panSpeed * dt);
  if (keys_pressed & FLAGS::ROTATE_DOWN)
    viewer.camera().rotatePitch(-panSpeed * dt);

  if (keys_pressed & FLAGS::STRAVE_FORWARD)
    viewer.camera().move(0.0, 0.0, +straveSpeed * dt);
  if (keys_pressed & FLAGS::STRAVE_BACKWARD)
    viewer.camera().move(0.0, 0.0, -straveSpeed * dt);
  if (keys_pressed & FLAGS::STRAVE_UP)
    viewer.camera().move(0.0, +straveSpeed * dt, 0.0);
  if (keys_pressed & FLAGS::STRAVE_DOWN)
    viewer.camera().move(0.0, -straveSpeed * dt, 0.0);
  if (keys_pressed & FLAGS::STRAVE_LEFT)
    viewer.camera().move(+straveSpeed * dt, 0.0, 0.0);
  if (keys_pressed & FLAGS::STRAVE_RIGHT)
    viewer.camera().move(-straveSpeed * dt, 0.0, 0.0);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  lastMousePosition = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  double constexpr smallAngle(0.4 / 180);
  if (event->buttons() & Qt::LeftButton) {
    double dx(event->pos().x() - lastMousePosition.x());
    double dy(event->pos().y() - lastMousePosition.y());

    lastMousePosition = event->pos();

    viewer.camera().rotateYaw(dx * smallAngle);
    viewer.camera().rotatePitch(dy * smallAngle);

    update();
  }
}

void GLWidget::pause() {
  if (timerID == 0) {
    timerID = startTimer(20);
    stopwatch.restart();
  } else {
    killTimer(timerID);
    timerID = 0;
  }
}
