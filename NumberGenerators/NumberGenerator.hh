#pragma once

class NumberGenerator {
public:
  virtual double uniform(double min, double max) = 0;
  virtual double gaussian(double mean, double standard_deviation) = 0;
};
