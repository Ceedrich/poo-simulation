#pragma once

#include "../Drawings/DrawingFrame.hh"
#include "Camera.hh"
#include "GLSphere.hh"
#include "Light.hh"
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class OpenGLViewer : public DrawingFrame {
public:
  enum SHADER_MODE {
    SHADER_MODE_PHONG,
    SHADER_MODE_MINIMAL,
  };
  virtual void draw(Particle const &) override;
  virtual void draw(MotionTrace const &) override;
  virtual void draw(Enclosure const &) override;
  virtual void draw(System const &) override;

  void init();

  void setProjection(QMatrix4x4 const &projection) {
    shaderProgram.setUniformValue("projection", projection);
  }

  Camera &camera() { return camera_; };
  Light &light() { return light_; }

  void setShaderMode(SHADER_MODE mode) { shaderMode = mode; }

private:
  void drawAxes(QMatrix4x4 const &point_of_view = QMatrix4x4(),
                bool colored = true);
  void drawSphere(QMatrix4x4 const &point_of_view, double red, double green,
                  double blue);

private:
  static constexpr const char *const SHADER_MODE_PHONG_LOCATION =
      ":/shaders/FragmentShaderPhong.glsl";
  static constexpr const char *const SHADER_MODE_MINIMAL_LOCATION =
      ":/shaders/FragmentShaderMinimal.glsl";
  SHADER_MODE shaderMode = SHADER_MODE_PHONG;
  QOpenGLShaderProgram shaderProgram;
  Light light_;
  Camera camera_;
  GLSphere sphere;
};
