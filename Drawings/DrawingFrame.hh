#pragma once
#include "Drawable.hh"

class MotionTrace;
class Particle;
class Enclosure;
class System;

/**
 * @brief The DrawingFrame class is an abstract base class that represents a
 * frame for drawing objects.
 *
 * The DrawingFrame class provides a common interface for drawing different
 * types of objects, such as particles and enclosures. Subclasses of
 * DrawingFrame must implement the draw() function for each type of object they
 * support.
 */
class DrawingFrame {
public:
  /**
   * @brief Virtual destructor for the DrawingFrame class.
   */
  virtual ~DrawingFrame() = default;

  /**
   * @brief Draws a particle on the drawing frame.
   *
   * @param particle The particle to be drawn.
   */
  virtual void draw(Particle const &) = 0;

  virtual void draw(MotionTrace const &) = 0;

  virtual void draw(Enclosure const &) = 0;

  virtual void draw(System const &) = 0;
};
