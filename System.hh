#pragma once
#include "Enclosure.hh"
#include "Particle.hh"
#include <memory>
#include <vector>

class System {
public:
  System() = default;
  System(double width, double length, double height)
      : enclosure(width, length, height) {}
      : random_draw(random_seed), enclosure(width, length, height) {}
  ~System() { delete_particles(); }

  // Pas possible de copier le systeme
  System(System const &) = delete;
  System operator=(System const &) = delete;

  void print(std::ostream &) const;
  void add_particle(std::unique_ptr<Particle> particle);
  void delete_particles();

private:
  Enclosure enclosure;
  std::vector<std::unique_ptr<Particle>> particles;
};

std::ostream &operator<<(std::ostream &out, System const &system);
