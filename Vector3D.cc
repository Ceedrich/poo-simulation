#include "Vector3D.hh"

#include <cmath>
#include <iostream>
#include <sstream>

std::string Vector3D::to_string() const {
  std::ostringstream strs;
  strs << x_ << " " << y_ << " " << z_;
  return strs.str();
}

void Vector3D::set_coords(double x, double y, double z) {
  this->x_ = x;
  this->y_ = y;
  this->z_ = z;
}

double Vector3D::dot_prod(const Vector3D &other) const {
  return (x_ * other.x_ + y_ * other.y_ + z_ * other.z_);
}

Vector3D Vector3D::cross_prod(const Vector3D &other) const {
  return ((*this) ^ other);
}

double Vector3D::norm2() const { return (x_ * x_ + y_ * y_ + z_ * z_); }

double Vector3D::norm() const { return std::sqrt(this->norm2()); }

Vector3D Vector3D::normalize() const {
  Vector3D vec = *this;
  vec *= 1 / this->norm();
  return vec;
}

// Operateurs
Vector3D Vector3D::operator-() const { return Vector3D(-x_, -y_, -z_); }
Vector3D &Vector3D::operator+=(Vector3D const &other) {
  x_ += other.x_;
  y_ += other.y_;
  z_ += other.z_;
  return *this;
}
Vector3D &Vector3D::operator-=(Vector3D const &other) {
  return *this += (-other);
}
Vector3D &Vector3D::operator*=(double scalar) {
  x_ *= scalar;
  y_ *= scalar;
  z_ *= scalar;
  return *this;
}
Vector3D &Vector3D::operator^=(Vector3D const &other) {
  double _x, _y, _z;
  _x = y_ * other.z_ - z_ * other.y_;
  _y = z_ * other.x_ - x_ * other.z_;
  _z = x_ * other.y_ - y_ * other.x_;
  x_ = _x;
  y_ = _y;
  z_ = _z;
  return *this;
}

void Vector3D::print(std::ostream &out) const { out << to_string(); }

double operator*(Vector3D const &vec1, Vector3D const &vec2) {
  return vec1.dot_prod(vec2);
}
const Vector3D operator^(Vector3D vec1, Vector3D const &vec2) {
  return (vec1 ^= vec2);
}

bool Vector3D::operator==(const Vector3D &other) const {
  return (std::abs(x_ - other.x_) < 1e-10 && std::abs(y_ - other.y_) < 1e-10 &&
          std::abs(z_ - other.z_) < 1e-10);
}

const Vector3D operator+(Vector3D vec1, Vector3D const &vec2) {
  return (vec1 += vec2);
}
const Vector3D operator-(Vector3D vec1, Vector3D const &vec2) {
  return (vec1 -= vec2);
}
const Vector3D operator*(Vector3D vec, double scalar) { return vec *= scalar; }
const Vector3D operator*(double scalar, Vector3D vec) { return vec *= scalar; }
