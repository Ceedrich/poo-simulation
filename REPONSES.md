# Reponses
Ce fichier contient les reponses aux questions posées dans les énoncés d'exercices.

## Semaine 02
### [Question P1.1] Comment représentez-vous ces vecteurs ? Comment sont-ils organisés : quels attributs ? quelles méthodes ? quels droits d'accès ?
La classe vecteur contient les coordonnées cartesienne (x, y, z) comme attributs privées et quelques méthodes publiques qui permettent de modifier/calculer avec des vecteurs. 

Les méthodes `to_string`, `print`, et `operator<<` donnent/affichent le vecteur en format `<x> <y> <z>`. //Was sind outputs? Und sind es nur diese Methoden?

En général, on *préfère* l'utilisation des operateurs standards (`+(=)`, `-(=)`, `==`, `<<` et `*(=)` pour multiplication par un scalaire) pour faciliter l'interface. //Was meint preferer? Sind sie implementiert? Gegenüber methoden &ja sind implementiert

Plus tard dans le projet encore plusieurs méthodes ont été implémenté.

## Semaine 04
### [Question P4.1] Avez-vous ajouté un constructeur de copie ? Pourquoi (justifiez votre choix) ?
Non, on n'a pas ajouté un constructeur de copie, mais il existe déjà un, implementé par le compilateur. Un `Vector3D` est une classe relativement simple ne contenant que trois attributs. C'est donc pas très chèr de faire une copie.

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
La méthode `dessine_sur(SupportADessin&)` (on l'a nommé `draw_on(DrawingFrame&)` en anglais) est une méthode virtuelle pure de la super-classe (abstraite) `Dessinable` (nommée `Drawable`) qui force les sous-classes de cette classe à implementer une méthode permettant de dessiner l'objet en question sur un `DrawingFrame`.


### [Question P8.1] A quoi faut-il faire attention pour les classes contenant des pointeurs ? Quelle(s) solution(s) est/sont envisageable(s) ?
En utilisant des pointeurs, il faut toujours faire attention de ne pas détruire l'objet pointée plusieurs fois ou avoir une addresse qui point sur un endroit dans la mémoire qui est invalide (puisqu'on a p.ex. déja détruit l'objet).
On a minimé ce problème en utilisant des `unique_ptr` qui admettent q'une seule pointeur sur un objet.


### [Question P8.2] Comment représentez vous la classe Systeme ? Expliquez votre conception (attributs, interface, ...).
Notre classe Systeme est construit d'une enceinte(*space*(Enclosure)) et d'une vecteur contenue des pointeurs de particules. Le vecteur est necessaire pour pouvoir avoir multiples particules dans le même système. On a un vecteur de pointeurs pour rendre possible le polymorphisme et dans ce cas utiliser les méthodes virtuelles propre de particule.
Tous les méthodes sont publique, comme ca on peut changer le système.


### [Question P8.3] Comment empêchez-vous cela (copie et affectation) ?
Pour l'affectation on fait un surcharge de l'opérateur = qui rendre l'affectation impossible (avec un delete) pour la copie on fait la même chose avec le constructeur du copie.
```c++
System(System const&) = delete;
System` operator=(System const&) = delete;
```

## Semaine 07

### [Question P9.1] Comment (et à quel(s) endroit(s)) intégrez vous ces deux aspects ?
// TODO

### [Question P9.2] Quelle est la complexité de l'algorithme de simulation lorsqu'il utilise cette méthode pour savoir si deux particules se rencontrent ?
En utilisant cet algorithme, il faut itérer sur tous les particules pour chaqu'une des particules. Il faut donc faire deux boucles "for". Cette méthode ajoute donc la complexité temporale $\Theta(n^2)$ où n est la nombre des particules.

##Semaine 9
###[Question P11.1] Si vous souhaitez voir l'enceinte, c.-à-d. la faire dessiner, comment devez vous modifier (ou pas) votre conception/votre code ?
//TODO

## Semaine 12

### [Question P13.1] Comment représentez-vous cette/ces nouvelle(s) particule(s) ? Où s'incri(ven)t-elle(s) dans votre conception ?
Ce particule peut être representé comme une sous-classe d'un des particules déjà existents.


### [Question P14.1] Avant de préciser les détails d'implémentation, quelle est la complexité temporelle pire cas de cette solution en fonction du nombre de particules ? [Attention : on suppose, par hypothèse même du modèle de gaz parfait, que les particules sont équiréparties dans l'enceinte. On suppose de plus que la taille d'une case est petite par rapport à la taille de l'enceinte. Ainsi on peut raisonnablement faire l'hypothèse que le nombre de particules par case est négligeable (O(1)) devant le nombre total de particules (c.-à-d. toutes les particules ne se retrouvent pas en même temps dans la même case). Quel(s) inconvénient(s) présente cependant cette solution ?
Pour déplacer les particules et actualiser les cases dans lesquels elles se trouvent, il faut parcourir tous les $n$ particules. C'est donc en $\Theta(n)$.
Ensuite, il suffit de parcourir tous les cases non-vides (maximum $n$ cases) et ainsi simuler les collisions de tous les particules dans le case. Lorsqu'on a supposer que la nombre des particules par case est négligeable, ceci est aussi possible en $\Theta(n)$.
Cette méthode a besoin de la création des nouveaux types. Mais, en raison de notre choix d'implémentation (voir P14.2), ni la classe `Particle` ni la classe `Enclosure` doit être modifié.

On a donc deux boucles en $\Theta(n)$ et finallement l'algorithme est en $\Theta(n)$.

###[Question P14.2]Comment et où avez-vous implémenté cette nouvelle façon de calculer les collisions ?
On l'a fait en travers d'un `std::unorderd_map` indexé par un nouveau type et sa "hash function". Ceci permet d'ajouter tous les particules à un case indexé par la position de la particule. Dans la deuxième boucle, on parcourt tous les cases contenant des particules (en utilisant les itérateurs sur le `unorderd_map`) et ensuite faire collider tous les particules dans la case.

Ceci évite de modifier les classes `Particle` et `Enclosure` et ne faut que deux nouveaux types qui sont isolées dans le fichier `System.cc` et ne sont pas visibles à l'extérieur.
