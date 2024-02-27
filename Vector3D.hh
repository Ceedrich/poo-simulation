#pragma once

#include <ostream>
#include <string>

class Vector3D {
 private:
  double x, y, z;

 public:
  Vector3D(double x, double y, double z);
  Vector3D();

  // Methods that change the vector
  void set_coords(double x, double y, double z);
  void add(const Vector3D &other);

  // Readonly Methods
  std::string to_string() const;
  void print() const;
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
  bool operator==(Vector3D const& other) const;
  Vector3D operator-() const;
};

// External operator overloads
const Vector3D operator+(Vector3D vec1, Vector3D const &vec2);
const Vector3D operator-(Vector3D vec1, Vector3D const &vec2);
const Vector3D operator*(Vector3D vec, double scalar);
const Vector3D operator*(double scalar, Vector3D vec);
std::ostream &operator<<(std::ostream &stream, Vector3D const &);
