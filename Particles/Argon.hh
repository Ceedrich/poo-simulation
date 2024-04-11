#pragma once

#include "Particle.hh"
#include <iostream>

class Argon : public Particle {
public:
  Argon(Vector3D r, Vector3D p, double m) : Particle(r, p, m) {}
  void print(std::ostream &out) const override;

  std::unique_ptr<Argon> copy() const { return std::make_unique<Argon>(*this); }

  std::unique_ptr<Particle> copyAsUniqueParticlePtr() const override {
    return copy();
  };
};
