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

void System::evolve(double dt) {
  for (size_t i = 0; i < particles.size(); ++i) {
    auto &p = particles[i];
    p->evolve(dt);
    p->collide(enclosure);
  }
  for (size_t i(particles.size()); i > 0; --i) {
    auto &p = particles[i - 1];
    for (size_t j(0); j < i - 1; ++j) {
      auto &q = particles[j];
      if (encounter(*p, *q)) {
        // cout << "La particule " << i
        //      << " entre en collision avec une autre particule " << j + 1
        //      << endl;
        // cout << "  avant le choc : " << endl;
        // cout << "    " << i << " : " << *p << endl;
        // cout << "    " << j + 1 << " : " << *q << endl;

        p->collide(*q, random_draw);

        // cout << "  après le choc : " << endl;
        // cout << "    " << i << " : " << *p << endl;
        // cout << "    " << j + 1 << " : " << *q << endl;
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

void System::setEncounterMethod(SYSTEM_ENCOUNTER_METHOD method) {
  switch (method) {
  case SYSTEM_ENCOUNTER_METHOD_PAVING:
    break;
  case SYSTEM_ENCOUNTER_METHOD_CENTER_OF_MASS:
    break;
  }
}

void System::draw_on(DrawingFrame &support) {
  support.draw(*this);
  enclosure.draw_on(support);
  for (auto const &p : particles) {
    p->draw_on(support);
  }
}

void System::fill(size_t count) {
  constexpr double temperature = 0.1;
  constexpr double specific_constant = Neon::SPECIFIC_CONSTANT;
  for (size_t _i(0); _i < count; ++_i) {
    Vector3D position(random_draw->uniform(0, enclosure.width()),
                      random_draw->uniform(0, enclosure.height()),
                      random_draw->uniform(0, enclosure.length()));
    Vector3D velocity(
        random_draw->gaussian(0.0, sqrt(specific_constant * temperature)),
        random_draw->gaussian(0.0, sqrt(specific_constant * temperature)),
        random_draw->gaussian(0.0, sqrt(specific_constant * temperature)));
    add_particle(Neon(position, velocity, 10));
  }
}

ostream &operator<<(ostream &out, System const &system) {
  system.print(out);
  return out;
}
