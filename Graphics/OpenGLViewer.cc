#include "OpenGLViewer.hh"
#include "../Particles/Helium.hh"
#include "../Particles/MotionTrace.hh"
#include "../System.hh"
#include "vertex_shader.hh"
#include <iostream>

void OpenGLViewer::init() {
  shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        ":/shaders/VertexShader.glsl");

  shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        graphicsLevel == GRAPHICS_LEVEL_HIGH
                                            ? PHONG_SHADER_LOCATION
                                            : SIMPLE_SHADER_LOCATION);

  shaderProgram.bindAttributeLocation("vertex", VertexShader::VertexID);
  shaderProgram.bindAttributeLocation("color", VertexShader::ColorID);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  shaderProgram.bind();

  sphere.initialize();
}

void OpenGLViewer::updateShaderUniformValues() {
  shaderProgram.setUniformValue("view", camera().view());

  if (graphicsLevel == GRAPHICS_LEVEL_HIGH) {
    shaderProgram.setUniformValue("light.position", light_.position());
    shaderProgram.setUniformValue("light.color", light_.color());

    shaderProgram.setUniformValue("light.ambient_intensity",
                                  light_.ambientIntensity());
    shaderProgram.setUniformValue("light.diffuse_intensity",
                                  light_.diffuseIntensity());
    shaderProgram.setUniformValue("light.specular_intensity",
                                  light_.specularIntensity());

    shaderProgram.setUniformValue("light.shininess", light_.shininess());

    shaderProgram.setUniformValue("viewPos", camera().position());
  }
}

void OpenGLViewer::draw(const Particle &p) {
  light_.setShininess(32);
  QMatrix4x4 m;
  m.translate(p.position().x(), p.position().y(), p.position().z());
  m.scale(0.5);
  drawSphere(m, p.color().x(), p.color().y(), p.color().z());
}

void OpenGLViewer::draw(const MotionTrace &p) {
  light_.setShininess(32);
  shaderProgram.setUniformValue("model", QMatrix4x4());

  glBegin(GL_LINE_STRIP);
  for (const auto &point : p.points()) {
    glVertex3f(point.x(), point.y(), point.z());
  }
  glEnd();
}
void OpenGLViewer::draw(const Enclosure &e) {
  light_.setShininess(10);
  constexpr QVector3D xColor(0.5, 0.5, 0.5);
  constexpr QVector3D yColor(0.7, 0.7, 0.7);
  constexpr QVector3D zColor(0.9, 0.9, 0.9);

  QMatrix4x4 m;
  m.scale(e.width(), e.height(), e.length());

  shaderProgram.setUniformValue("model", m);
  glBegin(GL_QUADS);

  shaderProgram.setAttributeValue(VertexShader::ColorID, xColor);
  // X = 0
  shaderProgram.setAttributeValue(VertexShader::NormalID, +1.0, +0.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +0.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +1.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +1.0, +1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +0.0, +1.0);

  // X = 1
  shaderProgram.setAttributeValue(VertexShader::NormalID, -1.0, +0.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +1.0, +1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +1.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +0.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +0.0, +1.0);

  shaderProgram.setAttributeValue(VertexShader::ColorID, yColor);
  // Y = 0
  shaderProgram.setAttributeValue(VertexShader::NormalID, 0.0, 1.0, 0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, 0.0, 0.0, 0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, 0.0, 0.0, 1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, 1.0, 0.0, 1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, 1.0, 0.0, 0.0);

  // Y = 1
  shaderProgram.setAttributeValue(VertexShader::NormalID, +0.0, -1.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +1.0, +1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +1.0, +1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +1.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +1.0, +0.0);

  shaderProgram.setAttributeValue(VertexShader::ColorID, zColor);
  // Z = 0
  shaderProgram.setAttributeValue(VertexShader::NormalID, +0.0, +0.0, +1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +0.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +0.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +1.0, +0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +1.0, +0.0);

  // Z = 1
  shaderProgram.setAttributeValue(VertexShader::NormalID, +0.0, +0.0, -1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +1.0, +1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +1.0, +0.0, +1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +0.0, +1.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, +0.0, +1.0, +1.0);
  glEnd();
}
void OpenGLViewer::draw(const System &) {}

void OpenGLViewer::drawSphere(const QMatrix4x4 &point_of_view, double red,
                              double green, double blue) {
  shaderProgram.setUniformValue("model", point_of_view);
  shaderProgram.setAttributeValue(VertexShader::ColorID, red, green, blue);
  sphere.draw(shaderProgram, VertexShader::VertexID, VertexShader::NormalID);
}
