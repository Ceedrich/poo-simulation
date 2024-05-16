#include "Enclosure.hh"

std::ostream &operator<<(std::ostream &stream, Enclosure const &e) {
  stream << "l : " << e.length() << "; w : " << e.width()
         << "; h : " << e.height();
  return stream;
}

void Enclosure::printRaw(std::ostream &out) const {
  out << length_ << " " << height_ << " " << width_ << std::endl;
}
