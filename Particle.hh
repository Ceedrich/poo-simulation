#pragma once

#include "Drawable.hh"
#include "Vector3D.hh"
#include <iostream>
#include <memory>

/**
 * @brief Represents a particle in a simulation.
 * 
 * The Particle class inherits from the Drawable class and represents a particle
 * with a position, speed, and mass.
 */
class Particle : public Drawable {
public:
  /**
   * @brief Constructs a Particle object with the given position, speed, and
   * mass.
   * 
   * @param pos The position of the particle.
   * @param v The speed of the particle.
   * @param m The mass of the particle.
   */
  Particle(Vector3D pos, Vector3D v, double m)
      : position_(pos), velocity_(v), mass_(m) {}

  /**
   * @brief Returns the position of the particle.
   *
   * @return The position of the particle.
   */
  Vector3D const &position() const { return position_; }

  /**
   * @brief Returns the velocity of the particle.
   *
   * @return The velocity of the particle.
   */
  Vector3D const &velocity() const { return velocity_; }

  /**
   * @brief Returns the mass of the particle.
   *
   * @return The mass of the particle.
   */
  double mass() const { return mass_; }

  /**
   * @brief Prints the particle's information to the output stream.
   * 
   * @param out The output stream to print to.
   */
  virtual void print(std::ostream &out) const;

  /**
   * @brief Draws the particle on a DrawingFrame object.
   * 
   * @param support The DrawingFrame object to draw on.
   */
  virtual void draw_on(DrawingFrame &support) override { support.draw(*this); }

  virtual std::unique_ptr<Particle> copy_as_unique_ptr() const = 0;

private:
  Vector3D position_; ///< The position of the particle.
  Vector3D velocity_; ///< The speed of the particle.
  double mass_;       ///< The mass of the particle.
};

/**
 * @brief Overloads the << operator to print the particle's information to the
 * output stream.
 * 
 * @param out The output stream to print to.
 * @param element The particle object to print.
 * @return The output stream after printing the particle's information.
 */
std::ostream &operator<<(std::ostream &out, Particle const &element);
