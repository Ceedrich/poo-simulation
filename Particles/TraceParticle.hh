#pragma once
#include "MotionTrace.hh"
#include "Particle.hh"

class TraceParticle : public Particle {
public:
  TraceParticle(Vector3D r, Vector3D v, double m) : Particle(r, v, m) {}

  void evolve(double dt) override;
  void printRaw(std::ostream &out) const override;

  std::unique_ptr<TraceParticle> copy() const {
    return std::make_unique<TraceParticle>(*this);
  }

  std::unique_ptr<Particle> copyAsUniqueParticlePtr() const override {
    return copy();
  }

  virtual void draw_on(DrawingFrame &support) override {
    support.draw(*this);
    motionTrace.draw_on(support);
  }

  Vector3D color() const override {
    return (1 / 255.0) * Vector3D(0x56, 0x6a, 0xcf);
  }

private:
  static constexpr unsigned int MAX_POINTS = 2000;
  MotionTrace motionTrace;
};
