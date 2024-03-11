#pragma once

#include <ostream>
#include <string>

class Vector3D {
private:
  double x_, y_, z_;

public:
  Vector3D(double x, double y, double z);
  Vector3D();

  // Accessors
  double x() const { return x_; }
  double y() const { return y_; }
  double z() const { return z_; }

  // Methods that change the vector
  void set_coords(double x, double y, double z);

  // Readonly Methods
  std::string to_string() const;
  bool is_equal(Vector3D const &other) const;

  double dot_prod(const Vector3D &other) const;
  Vector3D cross_prod(const Vector3D &other) const;

  double norm() const;
  double norm2() const;

  Vector3D normalize() const;

  // Operator overloads
  Vector3D &operator+=(Vector3D const &other);
  Vector3D &operator-=(Vector3D const &other);
  Vector3D &operator*=(double scalar);
  // Cross product
  Vector3D &operator^=(Vector3D const &other);
  bool operator==(Vector3D const &other) const;
  Vector3D operator-() const;
};

// External operator overloads
const Vector3D operator+(Vector3D vec1, Vector3D const &vec2);
const Vector3D operator-(Vector3D vec1, Vector3D const &vec2);
const Vector3D operator*(Vector3D vec, double scalar);
const Vector3D operator*(double scalar, Vector3D vec);
// Dot product
double operator*(Vector3D const &vec1, Vector3D const &vec2);
// Cross product
const Vector3D operator^(Vector3D vec1, Vector3D const &vec2);
std::ostream &operator<<(std::ostream &stream, Vector3D const &);
