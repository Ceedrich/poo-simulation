#pragma once

#include "Particle.hh"
#include <iostream>

class Neon : public Particle {
public:
  Neon(Vector3D r, Vector3D p, double m) : Particle(r, p, m) {}
  void print(std::ostream &out) const override;

  std::unique_ptr<Neon> copy() const { return std::make_unique<Neon>(*this); }

  std::unique_ptr<Particle> copyAsUniqueParticlePtr() const override {
    return copy();
  };
};
