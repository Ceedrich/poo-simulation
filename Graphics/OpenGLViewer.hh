#pragma once

#include "../Drawings/DrawingFrame.hh"
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class OpenGLViewer : public DrawingFrame {
public:
  virtual void draw(Particle const &) override;
  virtual void draw(Enclosure const &) override;
  virtual void draw(System const &) override;

  void init();

  void setProjection(QMatrix4x4 const &projection) {
    prog.setUniformValue("projection", projection);
  }

  void drawSomething(); // TODO

private:
  QOpenGLShaderProgram prog;
};
