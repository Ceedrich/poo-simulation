#include "GLWidget.hh"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTimerEvent>

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
  constexpr double smallAngle(5.0);
  constexpr double smallStep(0.5);

  switch (event->key()) {
  case Qt::Key::Key_Left:
    viewer.rotate(smallAngle, 0.0, -1.0, 0.0);
    break;
  case Qt::Key::Key_Right:
    viewer.rotate(smallAngle, 0.0, 1.0, 0.0);
    break;
  case Qt::Key::Key_Up:
    viewer.rotate(smallAngle, -1.0, 0.0, 0.0);
    break;
  case Qt::Key::Key_Down:
    viewer.rotate(smallAngle, 1.0, 0.0, 0.0);
    break;
  case KEY_FORWARD:
    viewer.translate(0.0, 0.0, smallStep);
    break;
  case KEY_BACKWARD:
    viewer.translate(0.0, 0.0, -smallStep);
    break;
  case KEY_LEFT:
    viewer.translate(smallStep, 0.0, 0.0);
    break;
  case KEY_RIGHT:
    viewer.translate(-smallStep, 0.0, 0.0);
    break;
  case KEY_DOWN:
    viewer.translate(0.0, smallStep, 0.0);
    break;
  case KEY_UP:
    viewer.translate(0.0, -smallStep, 0.0);
    break;
  case KEY_PAUSE:
    pause();
    break;
  case KEY_QUIT:
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
  if (event->buttons() & Qt::LeftButton) {
    constexpr double small_angle(.4);
    QPointF d(event->pos() - lastMousePosition);
    lastMousePosition = event->pos();

    viewer.rotate(small_angle * d.manhattanLength(), d.y(), d.x(), 0);

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
