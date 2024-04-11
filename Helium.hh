#pragma once

#include "Particle.hh"
#include <iostream>

class Helium : public Particle {
public:
  Helium(Vector3D r, Vector3D p, double m) : Particle(r, p, m) {}
  void print(std::ostream &out) const override;

  std::unique_ptr<Helium> copy() const {
    return std::make_unique<Helium>(*this);
  }

  std::unique_ptr<Particle> copyAsUniqueParticlePtr() const override {
    return copy();
  };
};
