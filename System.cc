#include "System.hh"

using namespace std;

void System::print(ostream& out) const {
    out<<"Le système est constitué de "<< elements.size() << " particules suivantes :"<<endl;
    for (auto element: elements){
        out << element << endl;
    }
}

void System::add_particle(Particle particle){
    elements.push_back(particle);
}

void System::delete_particles(){
    elements.clear();
}

ostream& operator<<(ostream& out, System const& system){
    system.print(out);
    return out;
}
