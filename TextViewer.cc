#include <iostream>

#include "Enclosure.hh"
#include "Particle.hh"
#include "TextViewer.hh"

using namespace std;

void TextViewer::draw(const Particle &p) { cout << p << endl; }
void TextViewer::draw(const Enclosure &e) {
  cout << "Enclosure : " << e << endl;
}
