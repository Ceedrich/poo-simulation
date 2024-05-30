#include "System.hh"
#include "Particles/TraceParticle.hh"
#include <fstream>
#include <unordered_map>

using namespace std;

void System::print(ostream &out) const {
  out << "Le système est constitué de " << particles.size()
      << " particules suivantes :" << endl;
  for (auto const &element : particles) {
    out << *element << endl;
  }
}

void System::printRaw(std::ostream &out) const {
  // epsilon temp
  // encounterMethod evolveMethod
  // particleCollisions enclosureCollisions timeElapsed
  out << "System " << epsilon_ << " " << temperature_ << " " //
      << encounterMethod << " " << evolveMethod << " "       //
      << numberOfParticleCollisions << " " << numberOfEnclosureCollisions << " "
      << timeElapsed;
}

void System::add_particle(Particle const &particle) {
  particles.push_back((particle.copyAsUniqueParticlePtr()));
}

void System::delete_particles() { particles.clear(); }

System System::fromFile(std::ifstream &file) {
  std::string delimiter;
  double epsilon, temperature;
  int encounterMethod, evolveMethod;
  double w, h, l;
  unsigned long int particleCollisions, enclosureCollisions;
  double elapsed;
  file >> delimiter;
  file >> epsilon >> temperature;
  file >> encounterMethod >> evolveMethod;
  file >> particleCollisions >> enclosureCollisions >> elapsed;
  file >> w >> h >> l;
  System s(w, h, l);
  s.setEpsilon(epsilon);
  s.setTemperature(temperature);
  s.setEncounterMethod((System::ENCOUNTER_METHOD)encounterMethod);
  s.setEvolveMethod((System::EVOLVE_METHOD)evolveMethod);
  s.numberOfParticleCollisions = particleCollisions;
  s.numberOfEnclosureCollisions = enclosureCollisions;
  while (!file.fail() && !file.eof()) {
    std::string delimiter;
    file >> delimiter;
    if (delimiter == "M") {
      // discard Trace
      getline(file, delimiter);
      continue;
    }
    double rx, ry, rz, vx, vy, vz, m;
    file >> rx >> ry >> rz >> vx >> vy >> vz >> m;
    if (delimiter == "Helium") {
      s.add_particle(Helium(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "Neon") {
      s.add_particle(Neon(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "Argon") {
      s.add_particle(Argon(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "TraceHelium") {
      s.add_particle(
          TraceParticle<Helium>(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "TraceNeon") {
      s.add_particle(
          TraceParticle<Neon>(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "TraceArgon") {
      s.add_particle(
          TraceParticle<Argon>(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
  }
  return s;
}

struct BoxPos {
  size_t x = 0;
  size_t y = 0;
  size_t z = 0;

  bool operator==(BoxPos const &p) const {
    return x == p.x && y == p.y && z == p.z;
  }
};

struct BoxPosHash {
  size_t operator()(BoxPos const &p) const {
    return (std::hash<int>()(p.x) ^ //
            std::hash<int>()(p.y) ^ //
            std::hash<int>()(p.z));
  }
};

BoxPos getBoxPos(Particle const &p, double epsilon) {
  return {
      (size_t)std::floor(p.position().x() / epsilon),
      (size_t)std::floor(p.position().y() / epsilon),
      (size_t)std::floor(p.position().z() / epsilon),
  };
}

void System::evolveAdvanced(System &s, double dt) {
  // setup maps
  std::unordered_map<BoxPos, vector<Particle *>, BoxPosHash> particleMap;

  // evolve the particles
  for (auto &p : s.particles) {
    p->evolve(dt);
    s.numberOfEnclosureCollisions += p->collide(s.enclosure_);
    particleMap[getBoxPos(*p, s.epsilon_)].push_back(p.get());
  }

  // Loop through boxes
  for (auto it = particleMap.begin(); it != particleMap.end(); ++it) {
    auto &box(it->second);
    for (size_t i(0); i < box.size(); ++i) {
      for (size_t j(i + 1); j < box.size(); ++j) {
        box[i]->collide(*box[j], s.random_draw);
        ++s.numberOfParticleCollisions;
      }
    }
  }
}

void System::evolveSimple(System &s, double dt) {
  for (auto &p : s.particles) {
    p->evolve(dt);
    s.numberOfEnclosureCollisions += p->collide(s.enclosure_);
  }
  vector<bool> collided(s.particles.size(), false);
  for (size_t _i(s.particles.size()); _i > 0; --_i) {
    size_t i = _i - 1;
    if (collided[i]) {
      continue;
    }
    auto &p = s.particles[i];
    for (size_t _j(_i - 1); _j > 0; --_j) {
      size_t j = _j - 1;
      if (collided[j]) {
        continue;
      }
      auto &q = s.particles[j];

      if (s.encounter(*p, *q)) {
        p->collide(*q, s.random_draw);
        ++s.numberOfParticleCollisions;
        collided[i] = true;
        collided[j] = true;
        break;
      }
    }
  }
}

bool System::encounter_paving(const Particle &p, const Particle &q,
                              double EPSILON) {
  int x1, y1, z1, x2, y2, z2;
  x1 = int(p.position().x() / EPSILON);
  y1 = int(p.position().y() / EPSILON);
  z1 = int(p.position().z() / EPSILON);
  x2 = int(q.position().x() / EPSILON);
  y2 = int(q.position().y() / EPSILON);
  z2 = int(q.position().z() / EPSILON);
  return ((x1 == x2) && (y1 == y2) && (z1 == z2));
}

bool System::encounter_center_of_mass(const Particle &p, const Particle &q,
                                      double EPSILON) {
  return (p.position() - q.position()).norm() < EPSILON;
}

void System::draw_on(DrawingFrame &support) {
  support.draw(*this);
  enclosure_.draw_on(support);
  for (auto const &p : particles) {
    p->draw_on(support);
  }
}

void System::fill(size_t count) {
  enum PARTICLE_TYPE {
    NEON = 0,
    HELIUM = 1,
    ARGON = 2,
  };
  for (size_t _i(0); _i < count; ++_i) {
    PARTICLE_TYPE particle_type = (PARTICLE_TYPE)random_draw->uniformInt(0, 2);
    switch (particle_type) {
    case NEON:
      addParticleAtRandomPlace<Neon>(*this);
      break;
    case HELIUM:
      addParticleAtRandomPlace<Helium>(*this);
      break;
    case ARGON:
      addParticleAtRandomPlace<Argon>(*this);
      break;
    }
  }
}

double System::averageKineticEnergy() const {
  if (particles.size() == 0)
    return 0.0;
  double energy = 0.0;
  for (auto const &p : particles) {
    energy += ((1.0 / 2.0) * p->mass() * p->velocity().norm2());
  }
  energy /= particles.size();

  return energy;
}

void System::evolve(double dt) {
  switch (evolveMethod) {
  case EVOLVE_METHOD_ADVANCED:
    evolveAdvanced(*this, dt);
    break;
  case EVOLVE_METHOD_SIMPLE:
    evolveSimple(*this, dt);
    break;
  }
  timeElapsed += dt;
}
bool System::encounter(const Particle &p, const Particle &q) {
  switch (encounterMethod) {
  case ENCOUNTER_METHOD_CENTER_OF_MASS:
    return encounter_center_of_mass(p, q, epsilon_);
    break;
  case ENCOUNTER_METHOD_PAVING:
    return encounter_paving(p, q, epsilon_);
    break;
  default:
    return false;
    break;
  }
}

void System::makeTraceParticle(size_t index) {
  if (index >= particles.size()) {
    cerr << "Particle at position " << index << "does not exist" << endl;
    return;
  }
  std::unique_ptr<Particle> x(particles[index]->copyAsUniqueParticlePtr());
  // I have to make a forbidden thing here and explicitly check for the type of
  // the particle because templates don't work with polymorphism. I can't have
  // `TraceParticle<Particle> x(TraceParticle<Helium>(...));`
  if (x->name() == "Helium") {
    std::unique_ptr<TraceParticle<Helium>> y(
        std::make_unique<TraceParticle<Helium>>(x));
    particles[index] = std::move(y);
  } else if (x->name() == "Neon") {
    std::unique_ptr<TraceParticle<Neon>> y(
        std::make_unique<TraceParticle<Neon>>(x));

    particles[index] = std::move(y);
  } else if (x->name() == "Argon") {
    std::unique_ptr<TraceParticle<Argon>> y(
        std::make_unique<TraceParticle<Argon>>(x));
    particles[index] = std::move(y);
  }
}
