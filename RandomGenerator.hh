#pragma once
#include "NumberGenerator.hh"
#include <random>

class RandomGenerator : public NumberGenerator {
private:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> uniform_distribution;

public:
  RandomGenerator(unsigned int seed = std::random_device()())
      : generator(seed) {}

  double uniform(double min, double max) override {
    return uniform_distribution(
        generator,
        std::uniform_real_distribution<double>::param_type{min, max});
  }
};
