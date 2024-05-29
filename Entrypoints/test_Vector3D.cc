#include "../Vector3D.hh"

#include <iostream>

using namespace std;

int main() {
  // Default constructor
  Vector3D v1;
  cout << "Default constructor: ";
  cout << "V1(" << v1 << ")" << endl;

  // Other constructor
  cout << "Other Constructor : ";
  Vector3D v2(3.14, 2.17, 42.0);
  cout << "V2(" << v2 << ")" << endl;

  // Accessors
  cout << "V2(" << v2 << ") has components: x=" << v2.x() << ", y=" << v2.y()
       << ", z=" << v2.z() << endl;

  // set_coords
  cout << "Set Coords: " << endl;
  v1.set_coords(200.0, 300.0, 600.0);
  cout << "V1(" << v1 << ")" << endl;

  // is_equal
  if (v1 == v1 && v2 == v2 && v1 != v2) {
    cout << "The vectors equal themselves and don't equal each other" << endl;
  } else {
    cout << "The vectors does not equal themselves or equal each other" << endl;
  }

  // Vector addition commutative
  if (v1 + v2 == v2 + v1) {
    cout << "V1+V2=V2+V1, Vector addition is commutative." << endl;
  } else {
    cout << "V1+V2!=V2+V1, Vector addition is not commutative." << endl;
  }

  // norm
  cout << "Norm of (" << v1 << "): " << v1.norm() << endl;
  // norm2
  cout << "Norm² of (" << v1 << "): " << v1.norm2() << endl;

  // normalize
  Vector3D v3(v1.normalize());
  cout << "Normalized vector of (" << v1 << "): " << "(" << v3 << ")" << endl;

  // Addition
  cout << "V1(" << v1 << ") + V2(" << v2 << ") = (" << v1 + v2 << ")" << endl;

  // Subtraction
  cout << "V1(" << v1 << ") - V2(" << v2 << ") = (" << v1 - v2 << ")" << endl;

  // Dot product
  cout << "V1(" << v1 << ") * V2(" << v2 << ") = (" << v1 * v2 << ")" << endl;

  // Cross product
  cout << "V1(" << v1 << ") x V2(" << v2 << ") = (" << (v1 ^ v2) << ")" << endl;

  // Scalar multiplication
  double s1(7), s2(1.0 / 100.0);
  cout << "V2(" << v2 << ") * " << s1 << " = (" << v2 * s1 << ")" << endl;
  cout << s2 << " * V1(" << v1 << ") = (" << s2 * v1 << ")" << endl;

  // Inverse
  cout << "Inverse of V1(" << v1 << "): (" << -v1 << ")" << endl;

  cout << "Print operation" << endl;
  cout << v2 << " == " << v2.x() << " " << v2.y() << " " << v2.z() << endl;
}
