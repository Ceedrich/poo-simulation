#pragma once
#include "MotionTrace.hh"
#include "Particle.hh"

class TraceParticle : public Particle {
public:
  TraceParticle(Vector3D r, Vector3D v, double m) : Particle(r, v, m) {}

  void evolve(double dt) override;

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

  Vector3D color() const override { return Vector3D(0.059, 0.161, 0.49); }

private:
  static constexpr unsigned int MAX_POINTS = 2000;
  MotionTrace motionTrace;
};
