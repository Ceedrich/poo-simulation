#pragma once

#include <ostream>
#include <string>

#include "Printable.hh"

/**
 * @brief Represents a 3D vector in Cartesian coordinates.
 *
 * The Vector3D class inherits from the Drawable class and provides methods for
 * vector operations.
 */
class Vector3D : public Printable {
private:
  double x_, y_, z_;

public:
  /**
   * @brief Constructs a Vector3D object with the given coordinates.
   *
   * @param x The x-coordinate of the vector.
   * @param y The y-coordinate of the vector.
   * @param z The z-coordinate of the vector.
   */
  Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z) {}

  /**
   * @brief Constructs a Vector3D object with default coordinates (0, 0, 0).
   */
  Vector3D() : Vector3D(0.0, 0.0, 0.0) {}

  // Accessors
  /**
   * @brief Returns the x-coordinate of the vector.
   *
   * @return The x-coordinate of the vector.
   */
  double x() const { return x_; }

  /*
   * @brief Returns the y-coordinate of the vector.
   *
   * @return The y-coordinate of the vector.
   */
  double y() const { return y_; }

  /**
   * @brief Returns the z-coordinate of the vector.
   *
   * @return The z-coordinate of the vector.
   */
  double z() const { return z_; }

  // Methods that change the vector
  /**
   * @brief Sets the coordinates of the vector.
   *
   * @param x The new x-coordinate of the vector.
   * @param y The new y-coordinate of the vector.
   * @param z The new z-coordinate of the vector.
   */
  void set_coords(double x, double y, double z);

  // Readonly Methods

  /**
   * @brief Checks if the vector is equal to another vector.
   *
   * @param other The other vector to compare with.
   * @return True if the vectors are equal, false otherwise.
   */
  bool is_equal(Vector3D const &other) const;

  /**
   * @brief Calculates the dot product of the vector with another vector.
   *
   * @param other The other vector.
   * @return The dot product of the vectors.
   */
  double dot_prod(const Vector3D &other) const;

  /**
   * @brief Calculates the cross product of the vector with another vector.
   *
   * @param other The other vector.
   * @return The cross product of the vectors.
   */
  Vector3D cross_prod(const Vector3D &other) const;

  /**
   * @brief Calculates the norm (magnitude) of the vector.
   *
   * @return The norm of the vector.
   */
  double norm() const;

  /**
   * @brief Calculates the squared norm (magnitude) of the vector.
   *
   * @return The squared norm of the vector.
   */
  double norm2() const;

  /**
   * @brief Returns a normalized version of the vector.
   *
   * @return The normalized vector.
   */
  Vector3D normalize() const;

  void print(std::ostream &out) const override;

  void printRaw(std::ostream &out) const override;

  // Operator overloads
  /**
   * @brief Adds another vector to the vector.
   *
   * @param other The other vector to add.
   * @return A reference to the modified vector.
   */
  Vector3D &operator+=(Vector3D const &other);

  /**
   * @brief Subtracts another vector from the vector.
   *
   * @param other The other vector to subtract.
   * @return A reference to the modified vector.
   */
  Vector3D &operator-=(Vector3D const &other);

  /**
   * @brief Multiplies the vector by a scalar.
   *
   * @param scalar The scalar value to multiply by.
   * @return A reference to the modified vector.
   */
  Vector3D &operator*=(double scalar);

  /**
   * @brief Calculates the cross product of the vector with another vector.
   *
   * @param other The other vector.
   * @return A reference to the modified vector.
   */
  Vector3D &operator^=(Vector3D const &other);

  /**
   * @brief Checks if the vector is equal to another vector.
   *
   * @param other The other vector to compare with.
   * @return True if the vectors are equal, false otherwise.
   */
  bool operator==(Vector3D const &other) const;

  /**
   * @brief Negates the vector.
   *
   * @return The negated vector.
   */
  Vector3D operator-() const;

  /**
   * @brief Returns a unit vector in the direction of the vector.
   *
   * @return The unit vector.
   */
  Vector3D operator~() const { return normalize(); }
};

// External operator overloads
/**
 * @brief Adds two vectors.
 *
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The sum of the vectors.
 */
const Vector3D operator+(Vector3D vec1, Vector3D const &vec2);

/**
 * @brief Subtracts one vector from another.
 *
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The difference between the vectors.
 */
const Vector3D operator-(Vector3D vec1, Vector3D const &vec2);

/**
 * @brief Multiplies a vector by a scalar.
 *
 * @param vec The vector.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
const Vector3D operator*(Vector3D vec, double scalar);

/**
 * @brief Multiplies a vector by a scalar.
 *
 * @param scalar The scalar value.
 * @param vec The vector.
 * @return The scaled vector.
 */
const Vector3D operator*(double scalar, Vector3D vec);

/**
 * @brief Calculates the dot product of two vectors.
 *
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The dot product of the vectors.
 */
double operator*(Vector3D const &vec1, Vector3D const &vec2);

/**
 * @brief Calculates the cross product of two vectors.
 *
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The cross product of the vectors.
 */
const Vector3D operator^(Vector3D vec1, Vector3D const &vec2);
