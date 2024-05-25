#pragma once

#include "Particle.hh"
#include <iostream>

class Neon : public Particle {
public:
  static constexpr double MOLAR_MASS = 20.1797;
  static constexpr double SPECIFIC_CONSTANT =
      1000 * IDEAL_GAS_CONSTANT / MOLAR_MASS;

  Neon(Vector3D r, Vector3D p, double m) : Particle(r, p, m) {}
  void print(std::ostream &out) const override;
  void printRaw(std::ostream &out) const override;

  std::unique_ptr<Neon> copy() const { return std::make_unique<Neon>(*this); }

  std::unique_ptr<Particle> copyAsUniqueParticlePtr() const override {
    return copy();
  };

  Vector3D color() const override {
    return (1 / 255.0) * Vector3D(0x44, 0xb7, 0xf0);
  }
};
