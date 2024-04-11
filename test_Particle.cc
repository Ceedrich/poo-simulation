#include "Particles/Neon.hh"
#include "Particles/Particle.hh"
#include <iostream>

using namespace std;

int main() {
  Neon p1(Vector3D(1.0, 1.0, 1.0), Vector3D(), 4.002602);
  Neon p2(Vector3D(1.0, 18.5, 1.0), Vector3D(0.0, 0.2, 0.0), 20.1797);
  Neon p3(Vector3D(1.0, 1.0, 3.1), Vector3D(0.0, 0.0, 0.5), 39.948);
  Neon p4(p2);

  cout << p1;
  cout << p2;
  cout << p3;
  cout << p4;

  return 0;
}
