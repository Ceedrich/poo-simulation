#pragma once
#include <ostream>

class Printable {
public:
  virtual void print(std::ostream &out) const = 0;
};

std::ostream &operator<<(std::ostream &out, Printable const &p); 
