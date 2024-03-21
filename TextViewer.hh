#pragma once
#include "DrawingFrame.hh"

class TextViewer : public DrawingFrame {
public:
  virtual void draw(const Vector3D &) override;
  virtual void draw(const Enclosure &) override;
};
