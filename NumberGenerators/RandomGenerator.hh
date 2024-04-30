#pragma once
#include "NumberGenerator.hh"
#include <random>

class RandomGenerator : public NumberGenerator {
private:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> uniform_distribution;
  std::normal_distribution<double> gaussian_distribution;
  std::uniform_int_distribution<int> int_distribution;

public:
  RandomGenerator(unsigned int seed = std::random_device()())
      : generator(seed) {}

  double uniform(double min, double max) override {
    return uniform_distribution(
        generator,
        std::uniform_real_distribution<double>::param_type{min, max});
  }

  double gaussian(double mean, double standard_deviation) override {
    return gaussian_distribution(
        generator,
        std::normal_distribution<double>::param_type{mean, standard_deviation});
  }

  int uniformInt(int min, int max) override {
    return int_distribution(
        generator, std::uniform_int_distribution<int>::param_type{min, max});
  }
};
