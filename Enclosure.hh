#pragma once
#include <ostream>

#include "Drawings/Drawable.hh"
#include "Drawings/DrawingFrame.hh"
#include "Vector3D.hh"

class Enclosure : public Drawable {
private:
  double width_;  // x
  double height_; // y
  double length_; // z

public:
  /**
   * @brief Constructs an Enclosure object with the given dimensions.
   *
   * @param w The width of the enclosure.
   * @param l The length of the enclosure.
   * @param h The height of the enclosure.
   */
  Enclosure(double w, double h, double l) : width_(w), height_(h), length_(l) {}

  /**
   * @brief Constructs a square Enclosure object with the given side length.
   *
   * @param l The side length of the square enclosure.
   */
  Enclosure(double l) : Enclosure(l, l, l) {}

  /**
   * @brief Constructs a default Enclosure object with a side length of 20.
   */
  Enclosure() : Enclosure(20) {}

  /**
   * @brief Returns the length of the enclosure.
   *
   * @return The length of the enclosure.
   */
  double length() const { return length_; }

  /**
   * @brief Returns the width of the enclosure.
   *
   * @return The width of the enclosure.
   */
  double width() const { return width_; }

  /**
   * @brief Returns the height of the enclosure.
   *
   * @return The height of the enclosure.
   */
  double height() const { return height_; }

  /**
   * @brief Draws the enclosure on the given DrawingFrame.
   *
   * @param support The DrawingFrame to draw on.
   */
  virtual void draw_on(DrawingFrame &support) override { support.draw(*this); }
};

/**
 * @brief Overloads the << operator to allow printing of Enclosure objects.
 *
 * @param stream The output stream.
 * @param enclosure The Enclosure object to print.
 * @return The modified output stream.
 */
std::ostream &operator<<(std::ostream &stream, Enclosure const &enclosure);
