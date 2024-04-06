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
  particles.push_back((particle.copy_as_unique_ptr()));
}

void System::delete_particles() { particles.clear(); }

ostream &operator<<(ostream &out, System const &system) {
  system.print(out);
  return out;
}
