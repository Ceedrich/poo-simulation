#include "Particle.hh"
#include "Vector3D.hh"
#include <iostream>

using namespace std;



  void Particle::print(ostream& out) const{
          out <<"pos : "<< position <<"; v : "<< speed <<"; m : "<< mass << endl;
          }



  ostream& operator<<(ostream& out, Particle element){
      element.print(out);
      return out;
  }




