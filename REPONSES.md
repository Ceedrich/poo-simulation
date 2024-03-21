# Reponses
Ce fichier contient les reponses aux questions posées dans les énoncés d'exercices.

## Semaine 02
### [Question P1.1] Comment représentez-vous ces vecteurs ? Comment sont-ils organisés : quels attributs ? quelles méthodes ? quels droits d'accès ?
La classe vecteur contient les coordonnées cardinales (x, y, z) comme attributs privées et quelques méthodes publiques qui permettent de modifier/calculer avec des vecteurs.

Les méthodes `to_string`, `print`, et `operator<<` donnent/affichent le vecteur en format `<x> <y> <z>` pour faciliter ces "outputs".

En général, on préfère l'utilisation des operateurs standards (`+(=)`, `-(=)`, `==`, `<<` et `*(=)` pour multiplication par un scalaire) pour faciliter l'interface.

## Semaine 04
### [Question P4.1] Avez-vous ajouté un constructeur de copie ? Pourquoi (justifiez votre choix) ?
Ouais, on n'a pas implementé un constructeur de copie, mais il existe, ajouté par le compilateur. Un `Vector3D` est une classe relativement simple ne contenant que trois attributs. C'est donc pas très chèr de faire une copie.

### [Question P4.2] Si l'on souhaitait ajouter un constructeur par coordonnées sphériques (deux angles et une longueur),

#### a] que cela impliquerait-il au niveau des attributs de la classe ?
Les attributs de la classe restent les mêmes, si on introduit un constructeur par coordonnées sphériques. Le constructeur fait le calcule pour transformer les coordonées sphériques données en coordonées cartesiennes.

#### b] quelle serait la difficulté majeure (voire l'impossibilité) de sa réalisation en C++ ? (C'est d'ailleurs pour cela qu'on ne vous demande pas de faire un tel constructeur !)
Le prototype d'un constructeur en coordonnées sphériques serait quelque chose comme
```c++
Vector3D(double r, double theta, double phi);
```
Mais ceci est en conflit avec le constructeur en coordonnées cartesiennes:
```c++
Vector3D(double x, double y, double z);
```

Les declarations ne sont pas possible sans ambiguïtés et donc impossible d'un façon claire (sans p.ex. ajouter des paramètres supplementaires pour les distinguer).

### [Question P4.3] Quels opérateurs avez vous introduits ?
On a intruduit les opérateurs suivantes:
- Les opérateurs logiques: `==`, `!=` (le dernier est automatiquement implementé par le compilateur)
- Les opérateurs pour la groupe additif: `+(=)`, `-(=)`, `-` (comme inversion)
- La multiplication scalaire `*`
- Le produit scalaire `*` et le produit vectoriel `^`
- L'opérateur pour l'affichage `<<`

## Semaine 06

### [Question P7.1] En termes de POO, quelle est donc la nature de la méthode dessine_sur() ?
La méthode `dessine_sur(SupportADessin&)` (on l'a nommé `draw_on(DrawingFrame&)` en anglais) est une méthode virtuelle pure de la super-classe (abstraite) `Dessinable` (nommée `Drawable`) qui force les enfants de cette classe a implementer la une méthode permettant de dessiner l'objet en question sur un `DrawingFrame`.





































