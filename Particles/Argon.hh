#pragma once

#include "Particle.hh"
#include <iostream>

class Argon : public Particle {
public:
  static constexpr double MOLAR_MASS = 39.948;
  static constexpr double SPECIFIC_CONSTANT =
      1000 * IDEAL_GAS_CONSTANT / MOLAR_MASS;

  Argon(Vector3D r, Vector3D p, double m) : Particle(r, p, m) {}
  void print(std::ostream &out) const override;

  std::unique_ptr<Argon> copy() const { return std::make_unique<Argon>(*this); }

  std::unique_ptr<Particle> copyAsUniqueParticlePtr() const override {
    return copy();
  };
};
