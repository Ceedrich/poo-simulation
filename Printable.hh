#pragma once
#include <ostream>

class Printable {
public:
  virtual void print(std::ostream &out) const = 0;
  virtual void printRaw(std::ostream &out) const;
};

std::ostream &operator<<(std::ostream &out, Printable const &p);
