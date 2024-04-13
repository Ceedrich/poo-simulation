#pragma once

#include "../Drawings/DrawingFrame.hh"
#include "GLSphere.hh"
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class OpenGLViewer : public DrawingFrame {
public:
  virtual void draw(Particle const &) override;
  virtual void draw(Enclosure const &) override;
  virtual void draw(System const &) override;

  void init();

  void setProjection(QMatrix4x4 const &projection) {
    shaderProgram.setUniformValue("projection", projection);
  }

  void translate(double x, double y, double z);
  void rotate(double angle, double dirX, double dirY, double dirZ);

private:
  void drawAxes(QMatrix4x4 const &point_of_view = QMatrix4x4(),
                bool colored = true);
  void drawSphere(QMatrix4x4 const &point_of_view, double red, double green,
                  double blue);

private:
  QOpenGLShaderProgram shaderProgram;
  QMatrix4x4 view_matrix;
  GLSphere sphere;
};
