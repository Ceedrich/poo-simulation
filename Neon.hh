#pragma once

#include "Particle.hh"
#include <iostream>

class Neon : public Particle {
public:
  Neon(Vector3D r, Vector3D p, double m) : Particle(r, p, m) {}
  void print(std::ostream &out) const override;
};
