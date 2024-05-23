#pragma once

#include "../Drawings/DrawingFrame.hh"
#include "Camera.hh"
#include "GLSphere.hh"
#include "Light.hh"
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class OpenGLViewer : public DrawingFrame {
public:
    /**
   * @brief The graphics level can either be high or low.
   */
  enum GRAPHICS_LEVEL {
    GRAPHICS_LEVEL_HIGH,
    GRAPHICS_LEVEL_LOW,
  };

  virtual void draw(Particle const &) override;

  virtual void draw(MotionTrace const &) override;

  virtual void draw(Enclosure const &) override;

  virtual void draw(System const &) override;

  /**
   * @brief Initializes OpenGLViewer
   */
  void init();

  /**
   * @brief Sets the projection matrix of the shader.
   * @param Projection Matrix
   */
  void setProjection(QMatrix4x4 const &projection) {
    shaderProgram.setUniformValue("projection", projection);
  }

  /**
   * @brief Returns camera
   * @return camera
   */
  Camera &camera() { return camera_; };

  /**
   * @brief Returns light
   * @return light
   */
  Light &light() { return light_; }

  /**
   * @brief Sets graphics level
   * @param graphics level
   */
  void setGraphicsLevel(GRAPHICS_LEVEL level) { graphicsLevel = level; }

  /**
   * @brief Updates shader uniform values
   */
  void updateShaderUniformValues();

private:
  /**
   * @brief Draws coordinate axes
   *
   * @param Point of view
   * @param bool if it is colored
   */
  void drawAxes(QMatrix4x4 const &point_of_view = QMatrix4x4(),
                bool colored = true);

  /**
   * @brief Draws a sphere
   *
   * @param point of view
   * @param Amount of red in the sphere.
   * @param Amount of green in the sphere.
   * @param Amount of blue in the sphere.
   */
  void drawSphere(QMatrix4x4 const &point_of_view, double red, double green,
                  double blue);

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
