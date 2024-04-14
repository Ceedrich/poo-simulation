#include "GLWidget.hh"
#include "Inputs.hh"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTimerEvent>
#include <cmath>

using std::asin, std::clamp;

void GLWidget::initializeGL() {
  viewer.init();
  timerID = startTimer(20);
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
  constexpr double smallAngle(5.0 * M_PI / 180);
  constexpr double smallStep(0.5);

  switch (event->key()) {
  case Qt::Key::Key_Left:
    viewer.camera().rotateYaw(+smallAngle);
    break;
  case Qt::Key::Key_Right:
    viewer.camera().rotateYaw(-smallAngle);
    break;
  case Qt::Key::Key_Up:
    viewer.camera().rotatePitch(+smallAngle);
    break;
  case Qt::Key::Key_Down:
    viewer.camera().rotatePitch(-smallAngle);
    break;
  case Inputs::FORWARD:
    viewer.camera().move(0.0, 0.0, +smallStep);
    break;
  case Inputs::BACKWARD:
    viewer.camera().move(0.0, 0.0, -smallStep);
    break;
  case Inputs::LEFT:
    viewer.camera().move(+smallStep, 0.0, 0.0);
    break;
  case Inputs::RIGHT:
    viewer.camera().move(-smallStep, 0.0, 0.0);
    break;
  case Inputs::DOWN:
    viewer.camera().move(0.0, -smallStep, 0.0);
    break;
  case Inputs::UP:
    viewer.camera().move(0.0, +smallStep, 0.0);
    break;
  case Inputs::PAUSE:
    pause();
    break;
  case Inputs::QUIT:
    close();
    break;
  }

  update();
}
void GLWidget::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);

  double dt = stopwatch.restart() / 1000.0;

  system.evolve(dt);
  update();
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
