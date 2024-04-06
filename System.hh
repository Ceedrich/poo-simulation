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
  // Factory for Exercice9
  static System exercice9() {
    System system;
    system.random_draw = std::unique_ptr<Ex9NumberGenerator>();
    return system;
  }

  System() : random_draw(std::make_unique<RandomGenerator>()) {}
  System(System &&) = default;
  System(double width, double length, double height)
      : random_draw(std::make_unique<RandomGenerator>()),
        enclosure(width, length, height) {}
  System(unsigned int random_seed)
      : random_draw(std::make_unique<RandomGenerator>(random_seed)) {}
  System(double width, double length, double height, unsigned int random_seed)
      : random_draw(std::make_unique<RandomGenerator>(random_seed)),
        enclosure(width, length, height) {}
  ~System() { delete_particles(); }

  // Pas possible de copier le systeme
  System(System const &) = delete;
  System operator=(System const &) = delete;

  void print(std::ostream &) const;
  void add_particle(Particle const &particle);
  void delete_particles();

private:
  std::unique_ptr<NumberGenerator> random_draw;
  Enclosure enclosure;
  std::vector<std::unique_ptr<Particle>> particles;
};

std::ostream &operator<<(std::ostream &out, System const &system);
