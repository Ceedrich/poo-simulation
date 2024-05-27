#include "Enclosure.hh"

void Enclosure::print(std::ostream &out) const {
  out << "l : " << length() << "; w : " << width() << "; h : " << height();
}

void Enclosure::printRaw(std::ostream &out) const {
  out << length_ << " " << height_ << " " << width_ << std::endl;
}

void Enclosure::augment() {
  width_ += 1.0;
  height_ += 1.0;
  length_ += 1.0;
}

void Enclosure::reduce() {
  width_ = std::max(width_ - 1, 1.0);
  height_ = std::max(height_ - 1, 1.0);
  length_ = std::max(length_ - 1, 1.0);
}
