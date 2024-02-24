# Prototypes
```c++
// SURCHARGE INTERNE
bool operator==(Classe const&) const; // (n'oublier pas !=)
bool operator>(Classe const&) const; // (n'oublier pas <, <= >=)

Classe& operator+=(Classe const&);
Classe& operator-=(Classe const&);

Classe& operator*=(autre_type const&);

Classe& operator++();
Classe& operator++(int inutile);

const Classe operator-() const;

// SURCHARGE EXTERNE
const Classe operator+(Classe, Classe const&);
const Classe operator-(Classe, Classe const&);

ostream& operator<<(ostream&, Classe const&);
const Classe operator*(autre_type, Classe const&);
```