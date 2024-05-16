#pragma once

#include "../Drawings/DrawingFrame.hh"
#include "Camera.hh"
#include "GLSphere.hh"
#include "Light.hh"
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class OpenGLViewer : public DrawingFrame {
public:
  enum GRAPHICS_LEVEL {
    GRAPHICS_LEVEL_HIGH,
    GRAPHICS_LEVEL_LOW,
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

  void setGraphicsLevel(GRAPHICS_LEVEL level) { graphicsLevel = level; }

  void updateShaderUniformValues();

private:
  void drawAxes(QMatrix4x4 const &point_of_view = QMatrix4x4(),
                bool colored = true);
  void drawSphere(QMatrix4x4 const &point_of_view, double red, double green,
                  double blue);

private:
  static constexpr const char *const PHONG_SHADER_LOCATION =
      ":/shaders/FragmentShaderPhong.glsl";
  static constexpr const char *const SIMPLE_SHADER_LOCATION =
      ":/shaders/FragmentShaderMinimal.glsl";
  GRAPHICS_LEVEL graphicsLevel = GRAPHICS_LEVEL_HIGH;
  QOpenGLShaderProgram shaderProgram;
  Light light_;
  Camera camera_;
  GLSphere sphere;
};
