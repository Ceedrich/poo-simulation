#include <iostream>

#include "Enclosure.hh"
#include "TextViewer.hh"
#include "Vector3D.hh"

using namespace std;

void TextViewer::draw(const Vector3D &vec) {
  cout << "Vector3D : " << vec << endl;
}
void TextViewer::draw(const Enclosure &e) {
  cout << "Enclosure : " << e << endl;
}
