# Cheatsheet

## Constructeurs
**Règle de trois**:
- Si on touche le *Destructeur*, le *Constructeur de copie* ou le *operateur=*, il faut aussi penser aux autres!!!

On peut passer une liste des valeurs: (pas de copie)
```c++
#include <initializer_list>
...
NomClasse(initializer_list<type> const& liste) {
    for (auto a : liste) { cout << a << endl; }
}
```
**Factory**: Si on a des ambiguÏtés lors du construction (p.ex. construir au coordonnées cartésiennes / sphériques):  
Dans ce cas, il est aussi utile de definir un *Constructeur de deplacement*.
```c++
class Complexe {
public:
  static Complexe from_polar(double r, double theta) {
    return Complexe(module * cos(theta), module * sin(theta));
  }

  Complexe(double x, double y) : x_(x), y_(y) {}
  Complexe(Complexe &&) = default;
};
```

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
const Classe operator+(Classe x, Classe const& y) { return x += y; }
const Classe operator-(Classe x, Classe const& y) { return x -= y; }

ostream& operator<<(ostream&, Classe const&);
const Classe operator*(autre_type, Classe const&);
```

Eviter de faire une conversion implicite: `explicit`

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
- Aussi redefinir `Classe operator=(Classe const other&);`
- `Classe(Classe &const) = delete;`

## Polymorphisme

### Définitions
- **surcharge**: même nom, mais paramètres différents
- **masquage**: entités de mêmes noms mais des portées différentes
  - Démasquer: (si la classe `B` hérite de `A`): `B b; b.A::f()`
- **substitution** des méthodes virtuelles -> résolution dynamique

### Methodes Virtuelles
- **Toujours définir les destructeurs comme virtuels!**
- Toujours utiliser `override` et `final` si possible
- Les méthodes virtuelles sont ignorées dans les constructeurs

Si on déclare une méthode comme *virtuelle*, le programme affiche la méthode propre du types (ça marche seulement si on a des références): 

```c++
class Base {
  virtual afficher() const { cout << "Base << endl; }
};
class Enfant : Base {
  afficher() const { cout << "Enfant" << endl; }
};

void afficher(vector<const Base&> const &vec) {
  for (auto e : vec) { vec.afficher(); }
}
```

### Destructeurs Virtuels
- liberer les ressource des *sous*-classes
- le destructeur de la super-classe doit être virtuel, si les sous-classes doivent liberer les ressources
- *gestion des resources par les sous-classes*

Règle des trois:
- destructeur, constructeur de copie, operateur=

### Classes Abstraites

Prototype des méthodes virtuelles pures: `virtual Type methode(...) = 0;`
