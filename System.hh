#pragma once
#include "Drawings/Drawable.hh"
#include "Drawings/DrawingFrame.hh"
#include "Enclosure.hh"
#include "NumberGenerators/Ex9NumberGenerator.hh"
#include "NumberGenerators/NumberGenerator.hh"
#include "NumberGenerators/RandomGenerator.hh"
#include "Particles/Argon.hh"
#include "Particles/Helium.hh"
#include "Particles/Neon.hh"
#include "Particles/Particle.hh"
#include <functional>
#include <memory>
#include <vector>

enum SYSTEM_ENCOUNTER_METHOD {
  SYSTEM_ENCOUNTER_METHOD_PAVING,
  SYSTEM_ENCOUNTER_METHOD_CENTER_OF_MASS,
};

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
    system.add_particle(Helium(Vector3D(1, 1, 1), Vector3D(), 4.002602));
    system.add_particle(
        Neon(Vector3D(1, 18.5, 1), Vector3D(0, 0.2, 0), 20.1797));
    system.add_particle(
        Argon(Vector3D(1, 1, 3.1), Vector3D(0, 0, -0.5), 39.948));

    return system;
  }

  static System prefilled() {
    System system(10.0, 20.0, 30.0);
    system.fill(40);
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
  System &operator=(System &&) = default;

  /**
   * @brief Constructor with enclosure dimensions.
   *
   * @param width The width of the enclosure.
   * @param length The length of the enclosure.
   * @param height The height of the enclosure.
   */
  System(double width, double height, double length)
      : random_draw(std::make_unique<RandomGenerator>()),
        enclosure(width, height, length) {}

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
  System(double width, double height, double length, unsigned int random_seed)
      : random_draw(std::make_unique<RandomGenerator>(random_seed)),
        enclosure(width, height, length) {}

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
   * @brief Fills the system randomly with particles
   * @param count The count of the particles
   */
  void fill(size_t count);

  /**
   * @brief Evolves the system over a given time step.
   *
   * @param dt The time step to evolve the system by.
   */
  void evolve(double dt);

  virtual void draw_on(DrawingFrame &support) override;

  void setEpsilon(double x) { EPSILON = x; }

  void setEncounterMethod(SYSTEM_ENCOUNTER_METHOD method);

private:
  double EPSILON = 1;

  static bool encounter_paving(Particle const &p, Particle const &q,
                               double EPSILON);
  static bool encounter_center_of_mass(Particle const &p, Particle const &q,
                                       double EPSILON);

  std::function<bool(Particle const &, Particle const &, double)> encounter =
      encounter_paving;

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
