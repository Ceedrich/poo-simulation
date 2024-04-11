#include "Enclosure.hh"
#include "Particles/Argon.hh"
#include "Particles/Helium.hh"
#include "Particles/Neon.hh"
#include "Text/TextViewer.hh"
#include "Vector3D.hh"
#include <iostream>

int main() {
  TextViewer textViewer;
  Neon neon(Vector3D(1, 2, 3), Vector3D(), 3.12);
  Argon argon(Vector3D(1, 0, 0), Vector3D(0, 0, 1), 4.4);
  Helium helium(Vector3D(12, 3, 9), Vector3D(0, -1, 0), 22.1);

  Enclosure e;

  textViewer.draw(neon);
  textViewer.draw(argon);
  textViewer.draw(e);
}
