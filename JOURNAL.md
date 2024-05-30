# Journal

## A faire:

- Anna: reponses week 4 Particules, particules, Système, reponses Système, journal updaten
- Cedric: Reponses différents gaz, journal updaten
  - Particle should not be drawable. The different kinds of particles should be.
  - Tâches ergänzen
  - Masse des particles

### Responsabilités

**Anna**

- JOURNAL, REPONSES, README, CONCEPTION
- Overview générale

**Cedric**

- Overview technique

## Semaine 1

Cette semaine, on a commancé a apprendre les concepts du programmation orienté objet. On a aussi mis en place le "toolchain" (Git, QTCreator, Cmake).

On a deja implementé une premier version de `Vector3D` qu'on va augmenter la semaine prochaine.

## Semaine 2

On a fini la classe `Vecteur3D` avec tous les surcharges d'opérateurs et constructeurs. Donc déjà au niveau de semaine quatre. Nous avons décidé de laisser la fonction `normalize` et de ne pas la replacé par le surcharge de signe ~, car il nous a semblé plus intuitive d'utiliser la fonction normalize, ce qui nous allons utilisé pour le projet.

## Semaine 4

Nous avons decider comment avancer d'ici et avons distribuer les taches des semaines 5 et 6. (Cedric va faire l'Enceinte et les Différents Gaz et Anna va faire les particules et le système).
Nous avons travailler sur les classes Particules et Enceinte.

Cedric a implementé la classe `Enceinte` (nomée `Enclosure`) et commencée a faire l'exercice P7. C'était difficile a faire, puisqu'il y a beaucoup des places où on peut oublier un `#include` etc.

## Semaine 5

Anna a fait la classe particule (`Particle`) et Cedric a fini la classe enceinte (`Enclosure`). Ils n'ont pas des questions auquel il faut répondre cette semaine.
On a fini la classe System et à répondu aux questions.

Cedric a fait l'exercice "Différents gaz" en utilisant de polymorphisme.

## Semaine 6

On a fait l'exercice P9.
Il était difficile de faire la première simulation, aussi avec le "number generator". Car pour pouvoir tester la classe des valeurs constantes étaient nécessaires.
En plus on a fait la number generator abstract class.

## Semaine 7

On a lu la tutoriel sur le graphisme, et on a crée une interface graphique. A ce point on a aussi fini le mooc et a donc pu ce concentrer sur le projet.

##Semaine 8
On a crée un interface graphique.
On a encore plus travailler sur le graphisme et on a fait la premier Simulation, ce qui a déjà bien fonctioné.

##Semaine 9
On a repondu aux questions restant.
On a commencé a travailler sur le "Lighting shader", pour lequel on a implementer le "phong model". Pour ca il a fallait de premièrement se mettre au courant avec cette modèle.
Pour le "phong model", on a implementé "ambient & diffuse lighing" mais pas encore "specular lighing".

##Semaine 10
On a amélioré la simulation. On a fixé le style de présentation et les possibilités du mouvement de la camera. De plus on a crée l'affichage des plusieurs informations sur le système et sur les contrôles, qu'on peut utiliser pour se naviger dans la simulation.

##Semaine 11
On a encore plus travailler sur le phong model en implémant "specular lighing". On a travailler sur le shader pour que ca fontionne pour notre modelle, cette un peu difficile car chez nous le shader doit savoir ou ce troue la camera.

##Semaine 12
Car les extensions ne sont pas encore online, on a encore améliorer notre Journal, les reponses et le projet. De plus nous avons travailler avec la classe `TraceParticle`, car on n'a pas pu utiliser du polymorphisme à cause de templates. Enfin on a décidé de faire un "test de classe" pour savoir quelle class-template il faut utiliser.

##Semaine 13
On a fait les extensions et on a amélioré le code. De plus on a commenter le code et on a testé tous les exercises.

##Semaine 14
On a encore travailler sur ameliorer le projet et on a fini P14, maintenant le system fontionne bien aussi avec 1000 particules. De plus on a complété les fichiers de conception, de responses, et le readme.
