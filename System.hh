#pragma once
#include "Drawings/Drawable.hh"
#include "Drawings/DrawingFrame.hh"
#include "Enclosure.hh"
#include "NumberGenerators/Ex9NumberGenerator.hh"
#include "NumberGenerators/NumberGenerator.hh"
#include "NumberGenerators/RandomGenerator.hh"
#include "Particles/Helium.hh"
#include "Particles/Particle.hh"
#include <memory>
#include <vector>

class System : public Drawable {
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

  static System prefilled() {
    System system;
    for (int x(0); x < 20; x += 5) {
      for (int y(0); y < 20; y += 5) {
        for (int z(0); z < 20; z += 5) {
          double vx = system.random_draw->uniform(-1.0, 1.0);
          double vy = system.random_draw->uniform(-1.0, 1.0);
          double vz = system.random_draw->uniform(-1.0, 1.0);
          double m = system.random_draw->uniform(0.0, 20.0);
          system.add_particle(
              Helium(Vector3D(x, y, z), Vector3D(vx, vy, vz), m));
        }
      }
    }
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

  virtual void draw_on(DrawingFrame &support) override;

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
