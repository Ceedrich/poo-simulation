#include "Particle.hh"
#include "Vector3D.hh"
#include <iostream>

using namespace std;

void Particle::print(ostream &out) const {
  out << "pos : " << position_ << "; v : " << velocity_ << "; m : " << mass_;
}
}

ostream &operator<<(ostream &out, Particle const &element) {
  element.print(out);
  return out;
}
