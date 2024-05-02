#pragma once
#include <QVector3D>

class Light {
public:
  Light(QVector3D pos = QVector3D(0.0, 0.0, 0.0),
        QVector3D color = QVector3D(1.0, 1.0, 1.0),
        float ambientIntensity = 0.3f, float diffuseIntensity = 0.6f,
        float specularIntensity = 0.5f)
      : position_(pos), color_(color), ambientIntensity_(ambientIntensity),
        diffuseIntensity_(diffuseIntensity),
        specularIntensity_(specularIntensity) {}

  QVector3D const &position() const { return position_; }
  QVector3D const &color() const { return color_; }
  float ambientIntensity() const { return ambientIntensity_; }
  float specularIntensity() const { return specularIntensity_; }
  float diffuseIntensity() const { return diffuseIntensity_; }

  void setColor(double r, double g, double b) { color_ = QVector3D(r, g, b); }
  void setPosition(double x, double y, double z) {
    position_ = QVector3D(x, y, z);
  }
  void setAmbientIntensity(float intensity) { ambientIntensity_ = intensity; }

  void move(double dx, double dy, double dz) {
    position_ += QVector3D(dx, dy, dz);
  }

private:
  QVector3D position_;
  QVector3D color_;
  float ambientIntensity_;
  float diffuseIntensity_;
  float specularIntensity_;
};
