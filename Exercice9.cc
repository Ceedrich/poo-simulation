#include "Argon.hh"
#include "Helium.hh"
#include "Neon.hh"
#include "System.hh"
#include <iostream>

using namespace std;

int main() {
  System system(System::exercice9());

  system.add_particle(Helium(Vector3D(1, 1, 1), Vector3D(), 4.002602));
  system.add_particle(Neon(Vector3D(1, 18.5, 1), Vector3D(0, 0.2, 0), 20.1797));
  system.add_particle(Argon(Vector3D(1, 1, 3.1), Vector3D(0, 0, -0.5), 39.948));

  cout << system << endl;

  cout << "Lancement de la simulation" << endl;
  for (unsigned int _i = 0; _i < 10; ++_i) {
    cout << "==========----------" << endl;
    system.evolve(1);
    cout << system;
  }

  return 0;
}
