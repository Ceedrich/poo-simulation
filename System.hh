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

class System : public Drawable, public Printable {
public:
  enum ENCOUNTER_METHOD {
    ENCOUNTER_METHOD_PAVING,
    ENCOUNTER_METHOD_CENTER_OF_MASS,
  };

  enum EVOLVE_METHOD {
    EVOLVE_METHOD_SINGLE,
    EVOLVE_METHOD_MULTIPLE,
  };

  struct Info {
    double averageKineticEnergy;
    double epsilon;
  };

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
        enclosure_(width, height, length) {}

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
        enclosure_(width, height, length) {}

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
  void print(std::ostream &out) const override;

  /**
   * @brief Prints the system to the output in an easy format to save and load
   * it
   * @param out The output stream to print to
   */
  void printRaw(std::ostream &out) const override;

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

  Enclosure const &enclosure() const { return enclosure_; }

  virtual void draw_on(DrawingFrame &support) override;

  void setEpsilon(double x) { EPSILON = x; }

  void setEncounterMethod(ENCOUNTER_METHOD method) { encounterMethod = method; }
  void setEvolveMethod(EVOLVE_METHOD method) { evolveMethod = method; }
  void setTemperature(double temp) { temperature = temp; }

  double averageKineticEnergy() const;
  double epsilon() const { return EPSILON; }

private:
  template <typename T> static void addParticleAtRandomPlace(System &s) {
    double constexpr specific_constant = T::SPECIFIC_CONSTANT;
    Vector3D position(s.random_draw->uniform(0, s.enclosure_.width()),
                      s.random_draw->uniform(0, s.enclosure_.height()),
                      s.random_draw->uniform(0, s.enclosure_.length()));
    Vector3D velocity(
        s.random_draw->gaussian(0.0, sqrt(specific_constant * s.temperature)),
        s.random_draw->gaussian(0.0, sqrt(specific_constant * s.temperature)),
        s.random_draw->gaussian(0.0, sqrt(specific_constant * s.temperature)));
    s.add_particle(T(position, velocity, 10.0));
  }

  double EPSILON = 1;
  double temperature = 0.1;
  ENCOUNTER_METHOD encounterMethod = ENCOUNTER_METHOD_PAVING;
  EVOLVE_METHOD evolveMethod = EVOLVE_METHOD_SINGLE;

  std::unique_ptr<NumberGenerator> random_draw;
  Enclosure enclosure_;
  std::vector<std::unique_ptr<Particle>> particles;

  // Encounter Method
  bool encounter(Particle const &p, Particle const &q) {
    switch (encounterMethod) {
    case ENCOUNTER_METHOD_CENTER_OF_MASS:
      return encounter_center_of_mass(p, q, EPSILON);
      break;
    case ENCOUNTER_METHOD_PAVING:
      return encounter_paving(p, q, EPSILON);
      break;
    }
    return false;
  }
  static bool encounter_paving(Particle const &p, Particle const &q,
                               double EPSILON);
  static bool encounter_center_of_mass(Particle const &p, Particle const &q,
                                       double EPSILON);
  // Evolve Method
  static void evolve_single(System &s, double dt);
  static void evolve_multiple(System &s, double dt);
};
