#pragma once
#include "../Drawings/DrawingFrame.hh"

/**
 * @brief The TextViewer class is a subclass of DrawingFrame that provides
 *        functionality for drawing text-based views of different objects.
 */
class TextViewer : public DrawingFrame {
public:
  virtual void draw(const Particle &) override;

  virtual void draw(const MotionTrace &) override;

  virtual void draw(const Enclosure &) override;

  virtual void draw(const System &) override;
};
