#pragma once
#include "../Drawings/DrawingFrame.hh"
#include <fstream>
#include <string>

/**
 * @brief The Filesaver class saves the system to a file in an easy
 *interpretable format
 **/
class FileSaver : public DrawingFrame {
public:
  FileSaver(std::string const &filename);
  ~FileSaver() { file_.close(); }
  virtual void draw(const Particle &) override;
  virtual void draw(const MotionTrace &) override;
  virtual void draw(const Enclosure &) override;
  virtual void draw(const System &) override;

private:
  std::ofstream file_;
};
