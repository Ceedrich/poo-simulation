#pragma once
#include "../Drawings/Drawable.hh"
#include "../Vector3D.hh"
#include <deque>

class MotionTrace : public Drawable {
public:
  MotionTrace(unsigned int max_points = 100) : max_points(max_points) {}
  virtual void draw_on(DrawingFrame &support) { support.draw(*this); }
  void addPoint(Vector3D const &p);

  std::deque<Vector3D> const &points() const { return points_; }

private:
  unsigned int max_points;
  std::deque<Vector3D> points_;
};
