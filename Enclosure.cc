#include "Enclosure.hh"

std::ostream &operator<<(std::ostream &stream, Enclosure const &e) {
  stream << "l : " << e.length() << "; w : " << e.width()
         << "; h : " << e.height();
  return stream;
}
