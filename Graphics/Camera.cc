#include "Camera.hh"
#include <cmath>
#include <iostream>

using std::sin, std::cos, std::acos, std::atan2;

QMatrix4x4 Camera::view() const {
  QMatrix4x4 m;
  m.lookAt(position, position + front(), WORLD_UP);
  return m;
}

void Camera::move(double x, double y, double z) {
  QVector3D right(QVector3D::crossProduct(WORLD_UP, front()));
  right.normalize();
  QVector3D front_(QVector3D::crossProduct(right, WORLD_UP));
  front_.normalize();
  position += (x * right + y * WORLD_UP + z * front_);
}

void Camera::rotateYaw(double angle) { yaw += angle; }
void Camera::rotatePitch(double angle) {
  pitch += angle;
  if (pitch <= -M_PI / 2) {
    pitch = -M_PI / 2;
  }
  if (pitch >= M_PI / 2) {
    pitch = M_PI / 2;
  }
}

QVector3D Camera::front() const {
  if (pitch <= -M_PI / 2)
    return QVector3D(0.0, -1.0, 0.0);
  if (pitch >= M_PI / 2)
    return QVector3D(0.0, 1.0, 0.0);

  double x(cos(pitch) * sin(yaw));
  double y(sin(pitch));
  double z(cos(pitch) * cos(yaw));
  return QVector3D(x, y, z);
}
