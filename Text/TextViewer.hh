#pragma once
#include "../Drawings/DrawingFrame.hh"

/**
 * @brief The TextViewer class is a subclass of DrawingFrame that provides
 *        functionality for drawing text-based views of different objects.
 */
class TextViewer : public DrawingFrame {
public:
  /**
   * @brief Draws a particle on the text-based view.
   *
   * @param particle The particle to be drawn.
   */
  virtual void draw(const Particle &) override;

  /**
   * @brief Draws an enclosure on the text-based view.
   *
   * @param enclosure The enclosure to be drawn.
   */
  virtual void draw(const Enclosure &) override;

  virtual void draw(const System &) override;
};
