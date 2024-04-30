#pragma once

class NumberGenerator {
public:
  virtual double uniform(double min, double max) = 0;
  virtual double gaussian(double mean, double standard_deviation) = 0;
  virtual int uniformInt(int min, int max) = 0;
};
