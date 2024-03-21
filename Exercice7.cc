#include "Argon.hh"
#include "Enclosure.hh"
#include "Neon.hh"
#include "TextViewer.hh"
#include "Vector3D.hh"
#include <iostream>

int main() {
  TextViewer textViewer;
  Neon neon(Vector3D(1, 2, 3), Vector3D(), 3.12);
  Argon argon(Vector3D(1, 0, 0), Vector3D(0, 0, 1), 4.4);

  Enclosure e;

  textViewer.draw(neon);
  textViewer.draw(argon);
  textViewer.draw(e);
}
