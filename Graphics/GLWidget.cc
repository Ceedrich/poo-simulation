#include "GLWidget.hh"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTimerEvent>

void GLWidget::initializeGL() { viewer.init(); }

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);

  QMatrix4x4 matrix;
  matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3,
                     1e5);
  viewer.setProjection(matrix);
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // TODO
  // system.draw_on(viewer);
}
