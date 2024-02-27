#include "Vector3D.hh"

#include <iostream>
#include <cmath>
#include <sstream>

// Constructors
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
Vector3D::Vector3D() : Vector3D(0.0, 0.0, 0.0) {}

bool Vector3D::is_equal(const Vector3D& other) const {
    return *this == other;
}

std::string Vector3D::to_string() const {
  std::ostringstream strs;
  strs << x << " " << y << " " << z;
  return strs.str();
}

void Vector3D::print() const { std::cout << this->to_string() << std::endl; }

void Vector3D::set_coords(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

void Vector3D::add(Vector3D const& other) {
  x += other.x;
  y += other.y;
  z += other.z;
}

double Vector3D::dot_prod(const Vector3D &other) const {
    return (x * other.x + y * other.y + z * other.z);
}

Vector3D Vector3D::cross_prod(const Vector3D &other) const {
   return Vector3D(
               y * other.z - z * other.y,
               z * other.x - x * other.z,
               x * other.y - y * other.x
   );
}

double Vector3D::norm2() const {
    return (x * x + y * y + z * z);
}

double Vector3D::norm() const {
    return std::sqrt(this->norm2());
}

Vector3D Vector3D::normalize() const {
    Vector3D vec = *this;
    vec *= 1/this->norm();
    return vec;
}

// Operateurs
Vector3D Vector3D::operator-() const { return Vector3D(-x, -y, -z); }
Vector3D& Vector3D::operator+=(Vector3D const& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}
Vector3D& Vector3D::operator-=(Vector3D const& other) {
  return *this += (-other);
}
Vector3D& Vector3D::operator*=(double scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

bool Vector3D::operator==(const Vector3D &other) const {
    return (
                std::abs(x - other.x) < 1e-10 &&
                std::abs(y - other.y) < 1e-10 &&
                std::abs(z - other.z) < 1e-10
   );
}

const Vector3D operator+(Vector3D vec1, Vector3D const& vec2) {
  return (vec1 += vec2);
}
const Vector3D operator-(Vector3D vec1, Vector3D const& vec2) {
  return (vec1 -= vec2);
}
const Vector3D operator*(Vector3D vec, double scalar) { return vec *= scalar; }
const Vector3D operator*(double scalar, Vector3D vec) { return vec *= scalar; }
std::ostream& operator<<(std::ostream& stream, Vector3D const& vec) {
  return stream << vec.to_string();
}
