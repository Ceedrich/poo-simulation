#pragma once

#include "../Drawings/DrawingFrame.hh"
#include "Camera.hh"
#include "GLSphere.hh"
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class OpenGLViewer : public DrawingFrame {
public:
  virtual void draw(Particle const &) override;
  virtual void draw(MotionTrace const &) override;
  virtual void draw(Enclosure const &) override;
  virtual void draw(System const &) override;

  void init();

  void setProjection(QMatrix4x4 const &projection) {
    shaderProgram.setUniformValue("projection", projection);
  }

  Camera &camera() { return camera_; };

private:
  void drawAxes(QMatrix4x4 const &point_of_view = QMatrix4x4(),
                bool colored = true);
  void drawSphere(QMatrix4x4 const &point_of_view, double red, double green,
                  double blue);

private:
  QOpenGLShaderProgram shaderProgram;
  Camera camera_;
  GLSphere sphere;
};
