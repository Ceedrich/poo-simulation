#include "Helium.hh"

void Helium::print(std::ostream &out) const {
  out << "particule Helium : ";
  Particle::print(out);
}
