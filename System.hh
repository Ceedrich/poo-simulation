#pragma once
#include "Enclosure.hh"
#include "Ex9NumberGenerator.hh"
#include "NumberGenerator.hh"
#include "Particle.hh"
#include "RandomGenerator.hh"
#include <memory>
#include <vector>

class System {
public:
  /**
   * @brief Factory method for Exercise 9.
   *
   * @return System object configured for Exercise 9.
   */
  static System exercice9() {
    System system;
    system.random_draw = std::make_unique<Ex9NumberGenerator>();
    return system;
  }

  /**
   * @brief Default constructor.
   */
  System() : random_draw(std::make_unique<RandomGenerator>()) {}

  /**
   * @brief Move constructor.
   */
  System(System &&) = default;

  /**
   * @brief Constructor with enclosure dimensions.
   *
   * @param width The width of the enclosure.
   * @param length The length of the enclosure.
   * @param height The height of the enclosure.
   */
  System(double width, double length, double height)
      : random_draw(std::make_unique<RandomGenerator>()),
        enclosure(width, length, height) {}

  /**
   * @brief Constructor with random seed.
   *
   * @param random_seed The random seed to use.
   */
  System(unsigned int random_seed)
      : random_draw(std::make_unique<RandomGenerator>(random_seed)) {}

  /**
   * @brief Constructor with enclosure dimensions and random seed.
   *
   * @param width The width of the enclosure.
   * @param length The length of the enclosure.
   * @param height The height of the enclosure.
   * @param random_seed The random seed to use.
   */
  System(double width, double length, double height, unsigned int random_seed)
      : random_draw(std::make_unique<RandomGenerator>(random_seed)),
        enclosure(width, length, height) {}

  /**
   * @brief Destructor.
   */
  ~System() { delete_particles(); }

  // Pas possible de copier le systeme
  System(System const &) = delete;
  System operator=(System const &) = delete;

  /**
   * @brief Prints the system to the output stream.
   *
   * @param out The output stream to print to.
   */
  void print(std::ostream &out) const;

  /**
   * @brief Adds a particle to the system.
   *
   * @param particle The particle to add.
   */
  void add_particle(Particle const &particle);

  /**
   * @brief Deletes all particles from the system.
   */
  void delete_particles();

  /**
   * @brief Evolves the system over a given time step.
   *
   * @param dt The time step to evolve the system by.
   */
  void evolve(double dt);

private:
  static double constexpr EPSILON = 1;

  std::unique_ptr<NumberGenerator> random_draw;
  Enclosure enclosure;
  std::vector<std::unique_ptr<Particle>> particles;
};

/**
 * @brief Overloaded stream insertion operator for System objects.
 *
 * @param out The output stream.
 * @param system The System object to insert into the stream.
 * @return The modified output stream.
 */
std::ostream &operator<<(std::ostream &out, System const &system);
