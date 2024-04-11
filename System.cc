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
      if (p->encounters(*q, EPSILON)) {
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

void System::draw_on(DrawingFrame &support) {
  support.draw(enclosure);
  for (auto const &p : particles) {
    support.draw(*p);
  }
}

ostream &operator<<(ostream &out, System const &system) {
  system.print(out);
  return out;
}
