#include "Printable.hh"

void Printable::printRaw(std::ostream &) const {}

std::ostream &operator<<(std::ostream &out, Printable const &p) {
  p.print(out);
  return out;
}
