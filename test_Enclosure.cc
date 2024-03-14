#include "Enclosure.hh"
#include <iostream>

using namespace std;

int main() {
  Enclosure e1;
  Enclosure e2(50);
  Enclosure e3(123, 14, 023);

  cout << "E1 : " << e1 << endl;
  cout << "E2 : " << e2 << endl;
  cout << "E3 : " << e3 << endl;

  return 0;
}
