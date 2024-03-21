#include "System.hh"
#include "Particle.hh"
#include "Helium.hh"
#include "Argon.hh"
#include "Neon.hh"
#include <iostream>

using namespace std;

int main() {
    System system1;
    System system2(5.0, 2.3, 1.0);
    system1.add_particle(Particle(Vector3D(1.2,2.3,3.4), Vector3D(2.4,1.5,2.0), 2.2));
    system2.add_particle(Particle(Vector3D(4,3,2), Vector3D(2,3,4), 55));
    system2.add_particle(Particle(Vector3D(), Vector3D(2.0,2.0,2.0), 5.7));
    system1.add_particle(Helium(Vector3D(1,2,3), Vector3D(), 39.123));

    cout << system1 << endl;
    cout<<system2<<endl;
    system1.delete_particles();
    cout<<system1<<endl;
}
