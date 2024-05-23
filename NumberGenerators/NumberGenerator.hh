#pragma once

class NumberGenerator {
public:
    /**
   * @brief Chooses a random number in intervall
   *
   * @param smallest possible number
   * @param biggest possible number
   * @return generated number
   */
  virtual double uniform(double min, double max) = 0;

    /**
   * @brief Chooses a number in intervall, considering gaussian distribution
   *
   * @param Mean of the distribution
   * @param Standard deviation
   * @return generated number
   */
  virtual double gaussian(double mean, double standard_deviation) = 0;

    /**
   * @brief Chooses a random whole number in intervall
   *
   * @param smallest possible number
   * @param biggest possible number
   * @return generated number
   */
  virtual int uniformInt(int min, int max) = 0;
};
