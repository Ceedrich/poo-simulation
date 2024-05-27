#pragma once
#include "Helium.hh"
#include "MotionTrace.hh"
#include "Particle.hh"

class TraceParticle : public Particle {
public:
  // TraceParticle is in fact acutally a Helium Particle.
  static constexpr double MOLAR_MASS = Helium::MOLAR_MASS;
  static constexpr double SPECIFIC_CONSTANT = Helium::SPECIFIC_CONSTANT;

  /**
   * @brief Constructor of TraceParticle
   *
   * @param Position vector
   * @param Speed vector
   * @param Mass
   */
  TraceParticle(Vector3D r, Vector3D v, double m) : Particle(r, v, m) {}

  /**
   * @brief Evolves position of the particle.
   * @param Time which has passed.
   */
  void evolve(double dt) override;
  void printRaw(std::ostream &out) const override;

  /**
   * @brief copies trace particle
   * @return copy as a unique pointer
   */
  std::unique_ptr<TraceParticle> copy() const {
    return std::make_unique<TraceParticle>(*this);
  }
  /**
   * @brief copies as unique particle pointer
   * @return copy as a unique pointer
   */
  std::unique_ptr<Particle> copyAsUniqueParticlePtr() const override {
    return copy();
  }

  virtual void draw_on(DrawingFrame &support) override {
    support.draw(*this);
    motionTrace.draw_on(support);
  }

  Vector3D color() const override {
    return (1 / 255.0) * Vector3D(0xff, 0xdb, 0x3b);
  }

private:
  static constexpr unsigned int MAX_POINTS = 2000;
  MotionTrace motionTrace;
};
