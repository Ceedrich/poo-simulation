#define _USE_MATH_DEFINES
#include "GLSphere.hh"
#include <cmath>

void GLSphere::initialize(GLuint slices, GLuint stacks) {
  vertices.clear();
  normals.clear();

  QVector<GLuint> indices0;
  QVector<GLuint> indices1;
  QVector<GLuint> indices2;

  GLuint size(2 + slices * (stacks - 1));

  vertices.reserve(3 * size);
  normals.reserve(3 * size);

  const double alpha(M_PI / double(stacks));
  const double beta(2.0 * M_PI / double(slices));

  vertices << 0.0 << 0.0 << 1.0;
  normals << 0.0 << 0.0 << 1.0;

  for (GLuint i(1); i < stacks; ++i) {
    for (GLuint j(0); j < slices; ++j) {
      float r = sin(i * alpha);
      float z = cos(i * alpha);
      float y = sin(j * beta) * r;
      float x = cos(j * beta) * r;

      vertices << x << y << z;
      normals << x << y << z;
    }
  }

  vertices << 0.0 << 0.0 << -1.0;
  normals << 0.0 << 0.0 << -1.0;

  indices0.reserve(slices + 2);
  for (GLuint i(0); i <= slices; ++i)
    indices0 << i;
  indices0 << 1;

  indices1.reserve((stacks - 2) * 4 * slices);
  for (GLuint i(0); i < stacks - 2; ++i) {
    for (GLuint j(0); j < slices; ++j) {
      indices1 << 1 + i * slices + j;
      indices1 << 1 + (i + 1) * slices + j;
      indices1 << 1 + (i + 1) * slices + (j + 1) % slices;
      indices1 << 1 + i * slices + (j + 1) % slices;
    }
  }

  indices2.reserve(slices + 2);
  for (GLuint i(1); i <= slices + 1; ++i)
    indices2 << size - i;
  indices2 << size - 2;

  vbo_sz = 3 * size * sizeof(GLfloat);
  vbo.create();
  vbo.bind();
  vbo.allocate(vertices.constData(), vbo_sz);
  vbo.release();

  ibo_sz[0] = indices0.size() * sizeof(GLuint);
  ibo_sz[1] = indices1.size() * sizeof(GLuint);
  ibo_sz[2] = indices2.size() * sizeof(GLuint);
  ibo.create();
  ibo.bind();
  ibo.allocate(ibo_sz[0] + ibo_sz[1] + ibo_sz[2]);
  ibo.write(0, indices0.constData(), ibo_sz[0]);
  ibo.write(ibo_sz[0], indices1.constData(), ibo_sz[1]);
  ibo.write(ibo_sz[0] + ibo_sz[1], indices2.constData(), ibo_sz[2]);
  ibo.release();
}

void GLSphere::draw(QOpenGLShaderProgram &program, int vertexAttributeLocation,
                    int normalAttributeLocation) {
  bind();

  program.enableAttributeArray(vertexAttributeLocation);
  program.setAttributeBuffer(vertexAttributeLocation, GL_FLOAT, 0, 3,
                             6 * sizeof(GLfloat));

  program.enableAttributeArray(normalAttributeLocation);
  program.setAttributeBuffer(normalAttributeLocation, GL_FLOAT,
                             3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

#define BUFFER_OFFSET(a) ((char *)nullptr + (a))

  glDrawElements(GL_TRIANGLE_FAN, ibo_sz[0] / sizeof(GLuint), GL_UNSIGNED_INT,
                 BUFFER_OFFSET(0));
  glDrawElements(GL_QUADS, ibo_sz[1] / sizeof(GLuint), GL_UNSIGNED_INT,
                 BUFFER_OFFSET(ibo_sz[0]));
  glDrawElements(GL_TRIANGLE_FAN, ibo_sz[2] / sizeof(GLuint), GL_UNSIGNED_INT,
                 BUFFER_OFFSET(ibo_sz[0] + ibo_sz[1]));

  program.disableAttributeArray(vertexAttributeLocation);
  program.disableAttributeArray(normalAttributeLocation);

  release();
}

void GLSphere::bind() {
  vbo.bind();
  ibo.bind();
}

void GLSphere::release() {
  ibo.release();
  vbo.release();
}
