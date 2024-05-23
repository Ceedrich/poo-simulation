#pragma once
#include "Inputs.hh"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QVector3D>

class Camera {
public:
    /**
   * @brief Constructor of the camera.
   *
   * @param Position vector of the Camera, by default (0,0,0)
   */
  Camera(QVector3D const &pos = QVector3D(0.0, 0.0, 0.0)) : position_(pos) {}

  /**
   * @brief Rotates Camera in a vertical direction
   *
   * @param Angle by which the camera will be rotated.
   */
  void rotateYaw(double angle);
  /**
   * @brief Rotates camera in a horizontal direction.
   *
   * @param Angle by which the camera will be rotated.
   */
  void rotatePitch(double angle);
  /**
   * @brief Moves the camera in space.
   *
   * @param Distance in x diretion by which the camera is shifted.
   * @param Distance in y diretion by which the camera is shifted.
   * @param Distance in z diretion by which the camera is shifted.
   */
  void move(double x, double y, double z);

  /**
   * @brief Sets the camera to a position.
   *
   * @param x-coodrinates of the camera.
   * @param y-coodrinates of the camera.
   * @param z-coodrinates of the camera.
   */
  void setPosition(double x, double y, double z) {
    position_ = QVector3D(x, y, z);
  }

  /**
   * @brief Adjusts camera so it "looks" to a certain point.
   *
   * @param x-coordinates of the point.
   * @param y-coordinates of the point.
   * @param z-coordinates of the point.
   */
  void lookAt(double x, double y, double z);

  /**
   * @brief Returns the view matrix
   * @return View matrix.
   */
  QMatrix4x4 view() const;

  /**
   * @brief Returns position
   * @return Postion of the camera.
   */
  QVector3D const &position() const { return position_; }

private:
  QVector3D front() const;
  static constexpr QVector3D WORLD_UP = QVector3D(0.0, 1.0, 0.0);
  QVector3D position_;
  double yaw = 0;
  double pitch = 0;
};
