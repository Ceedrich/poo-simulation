#include "Enclosure.hh"
#include "TextViewer.hh"
#include "Vector3D.hh"

int main() {
  TextViewer textViewer;
  Vector3D v1(3, 4, 5);
  Vector3D v2;
  Enclosure e(40, 10, 2);

  textViewer.draw(v1);
  textViewer.draw(v2);
  textViewer.draw(e);
}
