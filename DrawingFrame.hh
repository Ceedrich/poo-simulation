#pragma once
#include "Drawable.hh"

class Enclosure;
class Vector3D;

class DrawingFrame {
public:
  virtual ~DrawingFrame() = default;

  virtual void draw(Vector3D const &) = 0;
  virtual void draw(Enclosure const &) = 0;

  // virtual void draw(Neon const&) = 0;
  // virtual void draw(Argon const&) = 0;
  // virtual void draw(Enclosure const&) = 0;
  // virtual void draw(System const&) = 0;
};
