#pragma once
#include "Helium.hh"
#include "MotionTrace.hh"
#include "Particle.hh"

template <typename TParticle> class TraceParticle : public TParticle {
public:
  using TParticle::TParticle;

  /**
   * @brief Evolves position of the particle.
   * @param Time which has passed.
   */
  void evolve(double dt) override {
    motionTrace.addPoint(TParticle::position());
    TParticle::evolve(dt);
  };
  void printRaw(std::ostream &out) const override {
    out << "Trace";
    TParticle::printRaw(out);
  }

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
