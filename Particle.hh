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
   * @brief Constructs a Particle object with the given position, speed, and mass.
   * 
   * @param pos The position of the particle.
   * @param v The speed of the particle.
   * @param m The mass of the particle.
   */
  Particle(Vector3D pos, Vector3D v, double m)
      : position(pos), speed(v), mass(m) {}

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
  Vector3D position; ///< The position of the particle.
  Vector3D speed;    ///< The speed of the particle.
  double mass;       ///< The mass of the particle.
};

/**
 * @brief Overloads the << operator to print the particle's information to the output stream.
 * 
 * @param out The output stream to print to.
 * @param element The particle object to print.
 * @return The output stream after printing the particle's information.
 */
std::ostream &operator<<(std::ostream &out, Particle const &element);
