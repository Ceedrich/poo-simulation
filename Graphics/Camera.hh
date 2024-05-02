#pragma once
#include "Inputs.hh"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QVector3D>

class Camera {
public:
  Camera(QVector3D const &pos = QVector3D(0.0, 0.0, 0.0)) : position_(pos) {}

  void rotateYaw(double angle);
  void rotatePitch(double angle);

  void move(double x, double y, double z);
  void lookAt(double x, double y, double z);

  QMatrix4x4 view() const;
  QVector3D const &position() const { return position_; }

private:
  QVector3D front() const;
  static constexpr QVector3D WORLD_UP = QVector3D(0.0, 1.0, 0.0);
  QVector3D position_;
  double yaw = 0;
  double pitch = 0;
};
