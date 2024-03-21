#pragma once

#include "Drawable.hh"
#include "Vector3D.hh"
#include <iostream>

class Particle : public Drawable {
public:
  Particle(Vector3D pos, Vector3D v, double m)
      : position(pos), speed(v), mass(m) {}
  virtual void print(std::ostream &out) const;

  virtual void draw_on(DrawingFrame &support) override { support.draw(*this); }

private:
  Vector3D position;
  Vector3D speed;
  double mass;
};

std::ostream &operator<<(std::ostream &out, Particle const &element);
