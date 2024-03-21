#pragma once
#include "Drawable.hh"

class Particle;
class Enclosure;

class DrawingFrame {
public:
  virtual ~DrawingFrame() = default;

  virtual void draw(Particle const &) = 0;
  virtual void draw(Enclosure const &) = 0;

  // virtual void draw(Neon const&) = 0;
  // virtual void draw(Argon const&) = 0;
  // virtual void draw(Enclosure const&) = 0;
  // virtual void draw(System const&) = 0;
};
