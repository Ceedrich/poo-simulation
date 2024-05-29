#include "FileSaver.hh"
#include "../Enclosure.hh"
#include "../Particles/MotionTrace.hh"
#include "../Particles/Particle.hh"
#include "../System.hh"
#include <iostream>

FileSaver::FileSaver(std::string const &filename) : file_(filename) {
  if (file_.fail()) {
    std::cerr << "Opening file " << filename << " failed";
    file_.close();
    throw "FileOpeningError";
  }
}

void FileSaver::draw(const Particle &p) { p.printRaw(file_); }
void FileSaver::draw(const Enclosure &e) { e.printRaw(file_); }
void FileSaver::draw(const MotionTrace &t) {
  file_ << "M ";
  for (auto const &p : t.points()) {
    p.printRaw(file_);
    file_ << " ";
  }
  file_ << std::endl;
}
void FileSaver::draw(const System &s) {
  s.printRaw(file_);
  file_ << std::endl;
};
