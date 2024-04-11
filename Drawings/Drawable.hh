#pragma once

class DrawingFrame;

class Drawable {
public:
  virtual void draw_on(DrawingFrame &) = 0;
};
