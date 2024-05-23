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

  virtual ~DrawingFrame() = default;

  /**
   * @brief Draws a particle on the drawing frame.
   *
   * @param The particle to be drawn.
   */
  virtual void draw(Particle const &) = 0;

    /**
   * @brief Draws a motion trace on the drawing frame.
   *
   * @param Motion trace to be drawn.
   */
  virtual void draw(MotionTrace const &) = 0;

    /**
   * @brief Draws an enclosure on the drawing frame.
   *
   * @param Enclosure to be drawn.
   */
  virtual void draw(Enclosure const &) = 0;

    /**
   * @brief Draws a system on the drawing frame.
   *
   * @param System to be drawn.
   */
  virtual void draw(System const &) = 0;
};
