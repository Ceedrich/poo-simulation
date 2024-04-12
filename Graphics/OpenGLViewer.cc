#include "OpenGLViewer.hh"
#include "../Particles/Helium.hh"
#include "../System.hh"
#include "vertex_shader.hh"
#include <iostream>

void OpenGLViewer::init() {
  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,
                               ":/shaders/vertex_shader.glsl");

  prog.addShaderFromSourceFile(QOpenGLShader::Fragment,
                               ":/shaders/fragment_shader.glsl");

  prog.bindAttributeLocation("vertex", VertexID);
  prog.bindAttributeLocation("color", ColorID);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  prog.bind();

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

void OpenGLViewer::drawCube(QMatrix4x4 const &point_of_view) {
  prog.setUniformValue("vue_modele", point_of_view);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(ColorID, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(VertexID, +1.0, -1.0, -1.0);
  prog.setAttributeValue(VertexID, +1.0, +1.0, -1.0);
  prog.setAttributeValue(VertexID, +1.0, +1.0, +1.0);
  prog.setAttributeValue(VertexID, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(ColorID, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(VertexID, -1.0, -1.0, -1.0);
  prog.setAttributeValue(VertexID, -1.0, -1.0, +1.0);
  prog.setAttributeValue(VertexID, -1.0, +1.0, +1.0);
  prog.setAttributeValue(VertexID, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(ColorID, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(VertexID, -1.0, +1.0, -1.0);
  prog.setAttributeValue(VertexID, -1.0, +1.0, +1.0);
  prog.setAttributeValue(VertexID, +1.0, +1.0, +1.0);
  prog.setAttributeValue(VertexID, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(ColorID, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(VertexID, -1.0, -1.0, -1.0);
  prog.setAttributeValue(VertexID, +1.0, -1.0, -1.0);
  prog.setAttributeValue(VertexID, +1.0, -1.0, +1.0);
  prog.setAttributeValue(VertexID, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(ColorID, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(VertexID, -1.0, -1.0, +1.0);
  prog.setAttributeValue(VertexID, +1.0, -1.0, +1.0);
  prog.setAttributeValue(VertexID, +1.0, +1.0, +1.0);
  prog.setAttributeValue(VertexID, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(ColorID, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(VertexID, -1.0, -1.0, -1.0);
  prog.setAttributeValue(VertexID, -1.0, +1.0, -1.0);
  prog.setAttributeValue(VertexID, +1.0, +1.0, -1.0);
  prog.setAttributeValue(VertexID, +1.0, -1.0, -1.0);

  glEnd();
}

void OpenGLViewer::drawAxes(const QMatrix4x4 &point_of_view, bool colored) {
  prog.setUniformValue("view_model", view_matrix * point_of_view);
  glBegin(GL_LINES);

  if (colored) {
    prog.setAttributeValue(ColorID, 1.0, 0.0, 0.0);
  } else {
    prog.setAttributeValue(ColorID, 1.0, 1.0, 1.0); // white
  }
  // x
  prog.setAttributeValue(VertexID, 0.0, 0.0, 0.0);
  prog.setAttributeValue(VertexID, 1.0, 0.0, 0.0);
  // y
  if (colored)
    prog.setAttributeValue(ColorID, 0.0, 1.0, 0.0);
  prog.setAttributeValue(VertexID, 0.0, 0.0, 0.0);
  prog.setAttributeValue(VertexID, 0.0, 1.0, 0.0);
  // z
  if (colored)
    prog.setAttributeValue(ColorID, 0.0, 0.0, 1.0);
  prog.setAttributeValue(VertexID, 0.0, 0.0, 0.0);
  prog.setAttributeValue(VertexID, 0.0, 0.0, 1.0);

  glEnd();
}

void OpenGLViewer::drawSphere(const QMatrix4x4 &point_of_view, double red,
                              double green, double blue) {
  prog.setUniformValue("view_model", view_matrix * point_of_view);
  prog.setAttributeValue(ColorID, red, green, blue);
  sphere.draw(prog, VertexID);
}

void OpenGLViewer::drawParallelepipedeCubique(const QMatrix4x4 &point_of_view,
                                              double x, double y, double z) {
  prog.setUniformValue("vue_modele", point_of_view);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(ColorID, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(VertexID, +x, +0.0, +0.0);
  prog.setAttributeValue(VertexID, +x, +y, +0.0);
  prog.setAttributeValue(VertexID, +x, +y, +z);
  prog.setAttributeValue(VertexID, +x, +0.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(ColorID, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(VertexID, +0.0, +0.0, +0.0);
  prog.setAttributeValue(VertexID, +0.0, +0.0, +z);
  prog.setAttributeValue(VertexID, +0.0, +y, +z);
  prog.setAttributeValue(VertexID, +0.0, +y, +0.0);

  // face coté Y = +1
  prog.setAttributeValue(ColorID, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(VertexID, +0.0, +y, +0.0);
  prog.setAttributeValue(VertexID, +0.0, +y, +z);
  prog.setAttributeValue(VertexID, +x, +y, +z);
  prog.setAttributeValue(VertexID, +x, +y, +0.0);

  // face coté Y = -1
  prog.setAttributeValue(ColorID, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(VertexID, +0.0, +0.0, +0.0);
  prog.setAttributeValue(VertexID, +x, +0.0, +0.0);
  prog.setAttributeValue(VertexID, +x, +0.0, +z);
  prog.setAttributeValue(VertexID, +0.0, +0.0, +z);

  // face coté Z = +1
  prog.setAttributeValue(ColorID, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(VertexID, +0.0, +0.0, +z);
  prog.setAttributeValue(VertexID, +x, +0.0, +z);
  prog.setAttributeValue(VertexID, +x, +y, +z);
  prog.setAttributeValue(VertexID, +0.0, +y, +z);

  // face coté Z = -1
  prog.setAttributeValue(ColorID, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(VertexID, +0.0, +0.0, +0.0);
  prog.setAttributeValue(VertexID, +0.0, +y, +0.0);
  prog.setAttributeValue(VertexID, +x, +y, +0.0);
  prog.setAttributeValue(VertexID, +x, +0.0, +0.0);

  glEnd();
}
