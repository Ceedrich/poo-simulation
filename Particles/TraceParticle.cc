#include "TraceParticle.hh"

void TraceParticle::evolve(double dt) {
  motionTrace.addPoint(position());

  Particle::evolve(dt);
}
