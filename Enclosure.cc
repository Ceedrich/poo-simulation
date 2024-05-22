#include "Enclosure.hh"

void Enclosure::print(std::ostream &out) const {
  out << "l : " << length() << "; w : " << width() << "; h : " << height();
}

void Enclosure::printRaw(std::ostream &out) const {
  out << length_ << " " << height_ << " " << width_ << std::endl;
}
