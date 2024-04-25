#include <iostream>

#include "../Enclosure.hh"
#include "../Particles/MotionTrace.hh"
#include "../Particles/Particle.hh"
#include "TextViewer.hh"

using namespace std;

void TextViewer::draw(const Particle &p) { cout << p << endl; }
void TextViewer::draw(const Enclosure &e) {
  cout << "Enclosure : " << e << endl;
}

void TextViewer::draw(const MotionTrace &mt) {
  for (auto const &p : mt.points()) {
    cout << p << endl;
  }
}

void TextViewer::draw(const System &) { cout << "System: " << endl; }
