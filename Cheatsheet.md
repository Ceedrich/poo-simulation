# Cheatsheet

## Surcharge d'opérateurs
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

## Héritage
**Toujours appeller le constructeur de copie de la superclasse**

### Héritage des constructeurs
Les costructeurs heritées n'initialisent pas les attributs propres de la sous-classe.
```c++
class A {
public:
    A(int);
};
class B : public A {
using A::A;
};
```
**Attention: Constructeur de copie doit aussi copier les éléments dynamiquement alloués!**
- Faire une copie profonde (copie les objects, pas seulement les pointeurs)
- Aussi redefinir `Classe operator=(Classe const other&);
- `Classe(Classe &const) = delete;`
