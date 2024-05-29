#pragma once

#include "Particle.hh"
#include <iostream>

class Helium : public Particle {
public:
  static constexpr auto NAME = "Helim";
  static constexpr double MOLAR_MASS = 4.002602;
  static constexpr double SPECIFIC_CONSTANT =
      1000 * IDEAL_GAS_CONSTANT / MOLAR_MASS;

  Helium(Vector3D r, Vector3D p, double m) : Particle(r, p, m) {}
  void print(std::ostream &out) const override;
  void printRaw(std::ostream &out) const override;

  std::string name() const override { return NAME; }

  std::unique_ptr<Helium> copy() const {
    return std::make_unique<Helium>(*this);
  }

  std::unique_ptr<Particle> copyAsUniqueParticlePtr() const override {
    return copy();
  };
  Vector3D color() const override {
    return (1 / 255.0) * Vector3D(0x52, 0x5d, 0xf2);
  }
};
