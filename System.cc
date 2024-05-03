#include "System.hh"

using namespace std;

void System::print(ostream &out) const {
  out << "Le système est constitué de " << particles.size()
      << " particules suivantes :" << endl;
  for (auto const &element : particles) {
    out << *element << endl;
  }
}

void System::add_particle(Particle const &particle) {
  particles.push_back((particle.copyAsUniqueParticlePtr()));
}

void System::delete_particles() { particles.clear(); }

void System::evolve_multiple(System &s, double dt) {
  for (auto &p : s.particles) {
    p->evolve(dt);
    p->collide(s.enclosure_);
  }
  for (auto i(s.particles.rbegin()); i != s.particles.rend(); ++i) {
    auto &p(*i);
    for (auto j(i + 1); j != s.particles.rend(); ++i) {
      auto &q(*j);
      if (s.encounter(*p, *q)) {
        p->collide(*q, s.random_draw);
      }
    }
  }
}

void System::evolve_single(System &s, double dt) {
  for (auto &p : s.particles) {
    p->evolve(dt);
    p->collide(s.enclosure_);
  }
  vector<bool> collided(s.particles.size(), false);
  for (size_t _i(s.particles.size()); _i > 0; --_i) {
    size_t i = _i - 1;
    if (collided[i]) {
      continue;
    }
    auto &p = s.particles[i];
    for (size_t _j(_i - 1); _j > 0; --_j) {
      size_t j = _j - 1;
      if (collided[j]) {
        continue;
      }
      auto &q = s.particles[j];

      if (s.encounter(*p, *q)) {
        p->collide(*q, s.random_draw);
        collided[i] = true;
        collided[j] = true;
        break;
      }
    }
  }
}

bool System::encounter_paving(const Particle &p, const Particle &q,
                              double EPSILON) {
  int x1, y1, z1, x2, y2, z2;
  x1 = int(p.position().x() / EPSILON);
  y1 = int(p.position().y() / EPSILON);
  z1 = int(p.position().z() / EPSILON);
  x2 = int(q.position().x() / EPSILON);
  y2 = int(q.position().y() / EPSILON);
  z2 = int(q.position().z() / EPSILON);
  return ((x1 == x2) && (y1 == y2) && (z1 == z2));
}

bool System::encounter_center_of_mass(const Particle &p, const Particle &q,
                                      double EPSILON) {
  return (p.position() - q.position()).norm() < EPSILON;
}

void System::setEncounterMethod(ENCOUNTER_METHOD method) {
  switch (method) {
  case ENCOUNTER_METHOD_PAVING:
    encounter_method = encounter_paving;
    break;
  case ENCOUNTER_METHOD_CENTER_OF_MASS:
    encounter_method = encounter_center_of_mass;
    break;
  }
}

void System::setEvolveMethod(EVOLVE_METHOD method) {
  switch (method) {
  case EVOLVE_METHOD_SINGLE:
    evolve_method = evolve_single;
    break;
  case EVOLVE_METHOD_MULTIPLE:
    evolve_method = evolve_multiple;
    break;
  }
}

void System::draw_on(DrawingFrame &support) {
  support.draw(*this);
  enclosure_.draw_on(support);
  for (auto const &p : particles) {
    p->draw_on(support);
  }
}

void System::fill(size_t count) {
  constexpr double temperature = 0.1;
  constexpr double specific_constant = Neon::SPECIFIC_CONSTANT;
  for (size_t _i(0); _i < count; ++_i) {
    Vector3D position(random_draw->uniform(0, enclosure_.width()),
                      random_draw->uniform(0, enclosure_.height()),
                      random_draw->uniform(0, enclosure_.length()));
    Vector3D velocity(
        random_draw->gaussian(0.0, sqrt(specific_constant * temperature)),
        random_draw->gaussian(0.0, sqrt(specific_constant * temperature)),
        random_draw->gaussian(0.0, sqrt(specific_constant * temperature)));
    int i = random_draw->uniformInt(0, 2);
    switch (i) {
    case 0:
      add_particle(Neon(position, velocity, 10.0));
      break;
    case 1:
      add_particle(Argon(position, velocity, 10.0));
      break;
    case 2:
      add_particle(Helium(position, velocity, 10.0));
      break;
    default:
      add_particle(Neon(position, velocity, 10.0));
      break;
    }
  }
}

ostream &operator<<(ostream &out, System const &system) {
  system.print(out);
  return out;
}
