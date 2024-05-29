#include "Particle.hh"
#include "../Enclosure.hh"
#include "../NumberGenerators/RandomGenerator.hh"
#include "../Vector3D.hh"
#include <cmath>
#include <iostream>

using namespace std;

void Particle::print(ostream &out) const {
  out << "pos : " << position_ << "; v : " << velocity_ << "; m : " << mass_;
}

void Particle::printRaw(std::ostream &out) const {
  out << position() << " " << velocity() << " " << mass_ << std::endl;
}

void Particle::collide(Particle &other,
                       std::unique_ptr<NumberGenerator> &random_generator) {
  // 1. Calculer vg = m1/(m1 + m2)v1 + m2/(m1 + m2)v2
  Vector3D vg(mass_ / (mass_ + other.mass_) * velocity_ +
              other.mass_ / (mass_ + other.mass_) * other.velocity_);
  // 2. tirer au hasard un vecteur v0 de direction uniforme mais de norme
  // donnée, égale à celle de v1 - vg
  double L((this->velocity_ - vg).norm());
  double z(random_generator->uniform(-L, L));
  double phi(random_generator->uniform(0, 2 * M_PI));
  double r = sqrt(L * L - z * z);

  Vector3D v0(r * cos(phi), r * sin(phi), z);

  // 3. v1' = vg + v0
  velocity_ = vg + v0;
  // 4. v2' = vg - m1/m2 v0
  other.velocity_ = vg - (mass_ / other.mass_) * v0;
}

unsigned int Particle::collide(const Enclosure &enclosure) {
  unsigned int collisions(0);
  if (position_.x() > enclosure.width()) {
    position_ -= 2 * Vector3D(position_.x() - enclosure.width(), 0, 0);
    velocity_ = Vector3D(-velocity_.x(), velocity_.y(), velocity_.z());
    ++collisions;
  }
  if (position_.x() < 0) {
    position_ -= 2 * Vector3D(position_.x(), 0, 0);
    velocity_ = Vector3D(-velocity_.x(), velocity_.y(), velocity_.z());
    ++collisions;
  }
  if (position_.y() > enclosure.height()) {
    position_ -= 2 * Vector3D(0, position_.y() - enclosure.height(), 0);
    velocity_ = Vector3D(velocity_.x(), -velocity_.y(), velocity_.z());
    ++collisions;
  }
  if (position_.y() < 0) {
    position_ -= 2 * Vector3D(0, position_.y(), 0);
    velocity_ = Vector3D(velocity_.x(), -velocity_.y(), velocity_.z());
    ++collisions;
  }
  if (position_.z() > enclosure.length()) {
    position_ -= 2 * Vector3D(0, 0, position_.z() - enclosure.length());
    velocity_ = Vector3D(velocity_.x(), velocity_.y(), -velocity_.z());
    ++collisions;
  }
  if (position_.z() < 0) {
    position_ -= 2 * Vector3D(0, 0, position_.z());
    velocity_ = Vector3D(velocity_.x(), velocity_.y(), -velocity_.z());
    ++collisions;
  }

  return collisions;
}
