#pragma once

class DrawingFrame;

class Drawable {
public:
  virtual void draw_on(DrawingFrame &) = 0;

  virtual ~Drawable() = default;
  Drawable(Drawable const &) = default;
  Drawable &operator=(Drawable const &) = default;
  Drawable(Drawable &&) = default;
  Drawable &operator=(Drawable &&) = default;

  Drawable() = default;
};
