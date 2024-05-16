#include "Argon.hh"

void Argon::print(std::ostream &out) const {
  out << "particule Argon : ";
  Particle::print(out);
}

void Argon::printRaw(std::ostream &out) const {
  out << "Argon ";
  Particle::printRaw(out);
}
