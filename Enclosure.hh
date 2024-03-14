#pragma once
#include <ostream>

class Enclosure {
private:
  double length_, width_, height_;

public:
  Enclosure(double w, double l, double h) : length_(l), width_(w), height_(h) {}
  Enclosure(double l) : Enclosure(l, l, l) {}
  Enclosure() : Enclosure(20) {}

  double length() const { return length_; }
  double width() const { return width_; }
  double height() const { return height_; }
};

std::ostream &operator<<(std::ostream &stream, Enclosure const &);
