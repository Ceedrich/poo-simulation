#include "OpenGLViewer.hh"
#include "../System.hh"
#include "vertex_shader.hh"

void OpenGLViewer::init() {
  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,
                               ":/shaders/vertex_shader.glsl");

  prog.addShaderFromSourceFile(QOpenGLShader::Fragment,
                               ":/shaders/fragment_shader.glsl");

  prog.bindAttributeLocation("vertex", VertexID);
  prog.bindAttributeLocation("color", ColorID);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void OpenGLViewer::draw(const Particle &) {}
void OpenGLViewer::draw(const Enclosure &) {}
void OpenGLViewer::draw(const System &) {}
