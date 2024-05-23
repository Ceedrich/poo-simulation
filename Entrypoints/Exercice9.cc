#include "../Particles/Argon.hh"
#include "../Particles/Helium.hh"
#include "../Particles/Neon.hh"
#include "../System.hh"
#include <iostream>

using namespace std;

int main() {
  System system(System::exercice9());

  cout << system << endl;

  cout << "Lancement de la simulation" << endl;
  for (unsigned int _i = 0; _i < 10; ++_i) {
    cout << "==========----------" << endl;
    system.evolve(1);
    cout << system;
  }

  return 0;
}
