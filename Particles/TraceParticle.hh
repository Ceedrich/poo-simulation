#pragma once
#include "MotionTrace.hh"
#include "Particle.hh"

template <typename TParticle> class TraceParticle : public Particle {
public:
  TraceParticle(Vector3D const &p, Vector3D const &v, double m)
      : Particle(p, v, m) {}
  TraceParticle(std::unique_ptr<Particle> &ptr) : Particle(*ptr) {}

  /**
   * @brief Evolves position of the particle.
   * @param Time which has passed.
   */
  void evolve(double dt) override {
    motionTrace.addPoint(position());
    Particle::evolve(dt);
  };

  void print(std::ostream &out) const override {
    out << "particule " << name() << TParticle::NAME << " : ";
    Particle::print(out);
  }

  void printRaw(std::ostream &out) const override {
    out << name() << TParticle::NAME << " ";
    Particle::printRaw(out);
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

  std::string name() const override { return "Trace"; }

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
