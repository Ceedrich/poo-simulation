#pragma once
#include <QVector3D>

class Light {
public:
    /**
   * @brief Constructor of the Light class
   *
   * @param Position of the light
   * @param Color of the light
   * @param Ambient intensity
   * @param Diffuse intensity
   * @param Specular intensity
   * @param Shininess of the particules
   */
  Light(QVector3D pos = QVector3D(0.0, 0.0, 0.0),
        QVector3D color = QVector3D(1.0, 1.0, 1.0),
        float ambientIntensity = 0.2f, float diffuseIntensity = 0.6f,
        float specularIntensity = 0.5f, float shininess = 32)
      : position_(pos), color_(color), ambientIntensity_(ambientIntensity),
        diffuseIntensity_(diffuseIntensity),
        specularIntensity_(specularIntensity), shininess_(shininess) {}

  /**
   * @brief Returns position of the light.
   * @return Position.
   */
  QVector3D const &position() const { return position_; }

  /**
   * @brief Returns color of the light
   * @return Color of the light
   */
  QVector3D const &color() const { return color_; }

  /**
   * @brief Returns intensity of the ambient lighting.
   * @return Intensity ambient lighting.
   */
  float ambientIntensity() const { return ambient_ ? ambientIntensity_ : 0.0; }

  /**
   * @brief Returns intensity of the diffuse lighting.
   * @return Intensity diffuse lighting.
   */
  float diffuseIntensity() const { return diffuse_ ? diffuseIntensity_ : 0.0; }

  /**
   * @brief Returns intensity of the specular lighting.
   * @return specular intensity.
   */
  float specularIntensity() const {
    return specular_ ? specularIntensity_ : 0.0;
  }

  /**
   * @brief Returns shininess of particules.
   * @return shininess.
   */
  float shininess() { return shininess_; }

  /**
   * @brief Turns ambient lighting on/off.
   */
  void toggleAmbient() { ambient_ = !ambient_; }

  /**
   * @brief Turns diffuse lighting on/off.
   */
  void toggleDiffuse() { diffuse_ = !diffuse_; }

  /**
   * @brief Turns specular lighting on/off.
   */
  void toggleSpecular() { specular_ = !specular_; }

  /**
   * @brief Sets a new postion of the light.
   * @param x-coordinate of the light.
   * @param y-coordinate of the light.
   * @param z-coordinate of the light.
   */
  void setPosition(double x, double y, double z) {
    setPosition(QVector3D(x, y, z));
  }

  /**
   * @brief Sets a new position of the light.
   * @param Position as a vector.
   */
  void setPosition(QVector3D const &pos) { position_ = pos; }

  /**
   * @brief Sets ambient intensity
   * @param Intensity
   */
  void setAmbientIntensity(float intensity) { ambientIntensity_ = intensity; }

  /**
   * @brief Sets diffuse intensity.
   * @param Intensity
   */
  void setDiffuseIntensity(float intensity) { diffuseIntensity_ = intensity; }

  /**
   * @brief Sets specular intensity.
   * @param Intensity
   */
  void setSpecularIntensity(float intensity) { specularIntensity_ = intensity; }

  /**
   * @brief Sets shininess of the particules
   * @param Shininess
   */
  void setShininess(float shininess) { shininess_ = shininess; }

  /**
   * @brief Shifts position of the lighting
   *
   * @param Distance that light it is shifted in x direction.
   * @param Distance that light it is shifted in y direction.
   * @param Distance that light it is shifted in z direction.
   */
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
