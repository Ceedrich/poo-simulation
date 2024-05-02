#pragma once
#include <QVector3D>

class Light {
public:
  Light(QVector3D pos = QVector3D(0.0, 0.0, 0.0),
        QVector3D color = QVector3D(1.0, 1.0, 1.0),
        float ambientIntensity = 0.2f, float diffuseIntensity = 0.6f,
        float specularIntensity = 0.5f, float shininess = 32)
      : position_(pos), color_(color), ambientIntensity_(ambientIntensity),
        diffuseIntensity_(diffuseIntensity),
        specularIntensity_(specularIntensity), shininess_(shininess) {}

  QVector3D const &position() const { return position_; }
  QVector3D const &color() const { return color_; }
  float ambientIntensity() const { return ambient_ ? ambientIntensity_ : 0.0; }
  float diffuseIntensity() const { return diffuse_ ? diffuseIntensity_ : 0.0; }
  float specularIntensity() const {
    return specular_ ? specularIntensity_ : 0.0;
  }
  float shininess() { return shininess_; }

  void toggleAmbient() { ambient_ = !ambient_; }
  void toggleDiffuse() { diffuse_ = !diffuse_; }
  void toggleSpecular() { specular_ = !specular_; }

  void setPosition(double x, double y, double z) {
    setPosition(QVector3D(x, y, z));
  }
  void setPosition(QVector3D const &pos) { position_ = pos; }
  void setAmbientIntensity(float intensity) { ambientIntensity_ = intensity; }
  void setDiffuseIntensity(float intensity) { diffuseIntensity_ = intensity; }
  void setSpecularIntensity(float intensity) { specularIntensity_ = intensity; }
  void setShininess(float shininess) { shininess_ = shininess; }

  void move(double dx, double dy, double dz) {
    position_ += QVector3D(dx, dy, dz);
  }

private:
  QVector3D position_;
  QVector3D color_;
  bool ambient_ = true;
  bool diffuse_ = true;
  bool specular_ = true;
  float ambientIntensity_;
  float diffuseIntensity_;
  float specularIntensity_;
  float shininess_;
};
