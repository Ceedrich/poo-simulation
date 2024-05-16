#include "Neon.hh"

void Neon::print(std::ostream &out) const {
  out << "particule Néon : ";
  Particle::print(out);
}

void Neon::printRaw(std::ostream &out) const {
  out << "Neon ";
  Particle::printRaw(out);
}
