#pragma once
#include "../Drawings/Drawable.hh"
#include "../Drawings/DrawingFrame.hh"
#include "../Vector3D.hh"
#include <deque>

class MotionTrace : public Drawable {
public:
    /**
   * @brief Constructor of Motiontrace
   * @param The maximal number of points which can be traced, a hundred by default.
   */
  MotionTrace(unsigned int max_points = 100) : max_points(max_points) {}

  /**
   * @brief Draws the motion trace on the drawing frame.
   * @param Drawing frame
   */
  virtual void draw_on(DrawingFrame &support) { support.draw(*this); }

  /**
   * @brief Adds a point
   * @param Coordinates of the point to be added
   */
  void addPoint(Vector3D const &p);

  /**
   * @brief Returns points of motion trace.
   * @return vector of points
   */
  std::deque<Vector3D> const &points() const { return points_; }

private:
  unsigned int max_points;
  std::deque<Vector3D> points_;
};
