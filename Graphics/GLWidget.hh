#pragma once

#include "../System.hh"
#include "OpenGLViewer.hh"
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget {
public:
  GLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}
  virtual ~GLWidget() = default;

private:
  virtual void initializeGL() override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL() override;

  OpenGLViewer viewer;
  System system;
};
