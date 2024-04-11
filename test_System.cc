#include "Particles/Argon.hh"
#include "Particles/Helium.hh"
#include "Particles/Neon.hh"
#include "Particles/Particle.hh"
#include "System.hh"
#include <iostream>

using namespace std;

int main() {
  System system1;
  System system2(5.0, 2.3, 1.0);
  system1.add_particle(Helium(Vector3D(1, 1, 1), Vector3D(), 4.002602));
  system1.add_particle(
      Neon(Vector3D(1, 18.5, 1), Vector3D(0, 0.2, 0), 20.1797));
  system1.add_particle(
      Argon(Vector3D(1, 1, 3.1), Vector3D(0, 0, -0.5), 39.948));

  Neon neon(Vector3D(), Vector3D(), 5);

  system2.add_particle(neon);

  cout << system1 << endl;
  cout << system2 << endl;
  system1.delete_particles();
  cout << system1 << endl;
}
