#include "OpenGLViewer.hh"
#include "../Particles/Helium.hh"
#include "../System.hh"
#include "vertex_shader.hh"
#include <iostream>

void OpenGLViewer::init() {
  shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        ":/shaders/vertex_shader.glsl");

  shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        ":/shaders/fragment_shader.glsl");

  shaderProgram.bindAttributeLocation("vertex", VertexShader::VertexID);
  shaderProgram.bindAttributeLocation("color", VertexShader::ColorID);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  shaderProgram.bind();

  // Setup Light
  shaderProgram.setUniformValue("light.ambient", 1.0, 1.0, 1.0);
  shaderProgram.setUniformValue("light.ambient_intensity", 0.3f);
  shaderProgram.setUniformValue("light.position", 25.0, 25.0, 25.0);
  shaderProgram.setUniformValue("light.color", 1.0, 1.0, 1.0);

  sphere.initialize();

  view_matrix.setToIdentity();
}

void OpenGLViewer::translate(double x, double y, double z) {
  QMatrix4x4 m;
  m.translate(x, y, z);
  view_matrix = m * view_matrix;
}
void OpenGLViewer::rotate(double angle, double dirX, double dirY, double dirZ) {
  QMatrix4x4 m;
  m.rotate(angle, dirX, dirY, dirZ);
  view_matrix = m * view_matrix;
}

void OpenGLViewer::draw(const Particle &p) {
  QMatrix4x4 m;
  m.translate(p.position().x(), p.position().y(), p.position().z());
  m.scale(0.5);
  if (p.mass() <= 5.0) {
    drawSphere(m, 1.0, 0.0, 0.0);
  } else if (p.mass() <= 10) {
    drawSphere(m, 0.0, 1.0, 0.0);
  } else if (p.mass() <= 15) {
    drawSphere(m, 0.0, 0.0, 1.0);
  } else {
    drawSphere(m, 1.0, 1.0, 0.0);
  }
}
void OpenGLViewer::draw(const Enclosure &) {
  // drawParallelepipedeCubique(QMatrix4x4(), e.width(), e.height(),
  // e.length());
} // TODO
void OpenGLViewer::draw(const System &) { // TODO
  drawAxes();
}

void OpenGLViewer::drawAxes(const QMatrix4x4 &point_of_view, bool colored) {
  shaderProgram.setUniformValue("view", view_matrix);
  shaderProgram.setUniformValue("model", point_of_view);
  glBegin(GL_LINES);

  if (colored) {
    shaderProgram.setAttributeValue(VertexShader::ColorID, 1.0, 0.0, 0.0);
  } else {
    shaderProgram.setAttributeValue(VertexShader::ColorID, 1.0, 1.0,
                                    1.0); // white
  }
  // x
  shaderProgram.setAttributeValue(VertexShader::VertexID, 0.0, 0.0, 0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, 1.0, 0.0, 0.0);
  // y
  if (colored) {
    shaderProgram.setAttributeValue(VertexShader::ColorID, 0.0, 1.0, 0.0);
  }
  shaderProgram.setAttributeValue(VertexShader::VertexID, 0.0, 0.0, 0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, 0.0, 1.0, 0.0);
  // z
  if (colored) {
    shaderProgram.setAttributeValue(VertexShader::ColorID, 0.0, 0.0, 1.0);
  }
  shaderProgram.setAttributeValue(VertexShader::VertexID, 0.0, 0.0, 0.0);
  shaderProgram.setAttributeValue(VertexShader::VertexID, 0.0, 0.0, 1.0);

  glEnd();
}

void OpenGLViewer::drawSphere(const QMatrix4x4 &point_of_view, double red,
                              double green, double blue) {
  shaderProgram.setUniformValue("view", view_matrix);
  shaderProgram.setUniformValue("model", point_of_view);
  shaderProgram.setAttributeValue(VertexShader::ColorID, red, green, blue);
  sphere.draw(shaderProgram, VertexShader::VertexID, VertexShader::NormalID);
}
