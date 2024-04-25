#pragma once
#include <cmath>

#include "NumberGenerator.hh"

class Ex9NumberGenerator : public NumberGenerator {
  double uniform(double min, double) override {
    if (min == 0) { // phi
      return M_PI / 3;
    } else { // z
      return 0;
    }
  }
  double gaussian(double, double) override { return 0.0; }
};
