#pragma once
#include <ostream>

class Printable {
public:
    /**
     * @brief Prints representation from enclosure to outstream
     *
     * @param Stream which is used to print
     */
  virtual void print(std::ostream &out) const = 0;

    /**
     * @brief Prints representation from enclosure to outstream to save the state of the Enclosure
     *
     * @param Stream which is used to print
     */
  virtual void printRaw(std::ostream &out) const;
};

/**
 * @brief operator << is overloaded for a printable
 * @param Stream that prints
 * @param a printable object
 * @return Stream which was used to print
 */
std::ostream &operator<<(std::ostream &out, Printable const &p);
