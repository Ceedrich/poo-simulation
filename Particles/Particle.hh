#pragma once

#include "../Drawings/Drawable.hh"
#include "../Enclosure.hh"
#include "../NumberGenerators/NumberGenerator.hh"
#include "../Printable.hh"
#include "../Vector3D.hh"
#include <iostream>
#include <memory>

/**
 * COLOR Vectors obtained from
 * https://colorkit.co/palette/fc3041-ffdb3b-00cc25-44b7f0-525df2-9c45f2/
 *
 * #9c45f3 -> Default
 * #525df2 -> Helium
 * #44b7f0 -> Neon
 * #00cc25 -> Argon
 * #ffdb3b -> Trace
 * #fc3041
 *
 */

/**
 * @brief Represents a particle in a simulation.
 *
 * The Particle class inherits from the Drawable class and represents a particle
 * with a position, speed, and mass.
 */
class Particle : public Drawable, public Printable {
public:
  static constexpr double IDEAL_GAS_CONSTANT = 8.314472;

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
   * @brief Constructs a Particle object being a copy of another Particle
   * object.
   *
   * @param other The Particle object to copy.
   */
  Particle(Particle const &other) = default;

  virtual ~Particle() = default;
  virtual std::string name() const = 0;

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
  virtual void print(std::ostream &out) const override;

  /**
   * @brief Prints representation from enclosure to outstream to save the state
   * of the Enclosure
   *
   * @param Stream which is used to print
   */
  virtual void printRaw(std::ostream &out) const override;

  /**
   * @brief Draws the particle on a DrawingFrame object.
   *
   * @param support The DrawingFrame object to draw on.
   */
  virtual void draw_on(DrawingFrame &support) override { support.draw(*this); }

  /**
   * @brief Evolves the particle's position based on its velocity over a given
   * time interval.
   *
   * @param dt The time interval for which the particle's position will be
   * evolved.
   */
  virtual void evolve(double dt) { position_ += velocity_ * dt; }

  /**
   * @brief Collides the current particle with another particle.
   *
   * This function updates the state of the current particle and the other
   * particle based on the collision. The collision behavior is determined by
   * the implementation of this function.
   *
   * @param other The particle to collide with.
   * @param random_generator The random number generator used for any random
   * behavior during the collision.
   */
  void collide(Particle &other,
               std::unique_ptr<NumberGenerator> &random_generator);

  /**
   * @brief Collides the particle with the given enclosure.
   *
   * This function updates the state of the particle after colliding with the
   * enclosure.
   *
   * @param enclosure The enclosure to collide with.
   *
   * @return The number of collisions with the enclosure
   */
  unsigned int collide(Enclosure const &enclosure);

  /**
   * @brief Creates a copy of the particle as a unique pointer.
   *
   * @return A unique pointer to the copied particle.
   */
  virtual std::unique_ptr<Particle> copyAsUniqueParticlePtr() const = 0;

  /**
   * @brief color of the particle
   * @return (r, g, b) in a vector as (x, y, z)
   */
  virtual Vector3D color() const {
    return (1 / 255.0) * Vector3D(0x9c, 0x45, 0xf3);
  }

private:
  Vector3D position_; ///< The position of the particle.
  Vector3D velocity_; ///< The speed of the particle.
  double mass_;       ///< The mass of the particle.
};
