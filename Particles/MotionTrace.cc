#include "MotionTrace.hh"

void MotionTrace::addPoint(const Vector3D &p) {
  points_.push_back(p);
  if (points_.size() > max_points) {
    points_.pop_front();
  }
}
