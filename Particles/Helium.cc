#include "Helium.hh"

void Helium::print(std::ostream &out) const {
  out << "particule Helium : ";
  Particle::print(out);
}

void Helium::printRaw(std::ostream &out) const {
  out << "Helium ";
  Particle::printRaw(out);
}
