#pragma once

#include "Particle.hh"
#include <iostream>

class Argon : public Particle {
public:
  Argon(Vector3D r, Vector3D p, double m) : Particle(r, p, m) {}
  void print(std::ostream &out) const override;
};
