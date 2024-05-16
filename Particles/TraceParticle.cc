#include "TraceParticle.hh"

void TraceParticle::evolve(double dt) {
  motionTrace.addPoint(position());

  Particle::evolve(dt);
}

void TraceParticle::printRaw(std::ostream &out) const {
  out << "Trace ";
  Particle::printRaw(out);
}
