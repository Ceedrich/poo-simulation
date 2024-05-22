#include "Printable.hh"

std::ostream &operator<<(std::ostream& out, Printable const& p) {
    p.print(out);
    return out;
}
