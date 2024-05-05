#include "Camera.hh"
#include <cmath>
#include <iostream>

using std::sin, std::cos, std::acos, std::atan2;

QMatrix4x4 Camera::view() const {
  QMatrix4x4 m;
  m.lookAt(position_, position_ + front(), WORLD_UP);
  return m;
}

void Camera::move(double x, double y, double z) {
  QVector3D right(QVector3D::crossProduct(WORLD_UP, front()).normalized());
  QVector3D front_(QVector3D::crossProduct(right, WORLD_UP).normalized());
  position_ += (x * right + y * WORLD_UP + z * front_);
}

void Camera::lookAt(double x, double y, double z) {
  QVector3D dir(
      QVector3D(x - position_.x(), y - position_.y(), z - position_.z())
          .normalized());

  yaw = atan2(dir.x(), dir.z());
  pitch = atan(dir.y());
}

void Camera::rotateYaw(double angle) { yaw += angle; }
void Camera::rotatePitch(double angle) {
  constexpr double epsilon = 0.1;
  constexpr double upper_bound = M_PI / 2 - epsilon;
  constexpr double lower_bound = -M_PI / 2 + epsilon;
  pitch += angle;
  if (pitch <= lower_bound) {
    pitch = lower_bound;
  }
  if (pitch >= upper_bound) {
    pitch = upper_bound;
  }
}

QVector3D Camera::front() const {
  double x(cos(pitch) * sin(yaw));
  double y(sin(pitch));
  double z(cos(pitch) * cos(yaw));
  return QVector3D(x, y, z);
}
