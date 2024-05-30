# Conceptions

On a écrit tous les classes du projet et un petit description pour chaque classe.
Les classes indentés sont les sous-classes de les classes non-indentés au dessus.

## Classes de base

- `Vector3D`: represente un vecteur en 3D et permet les opérations de base.

- `NumberGenerator`: Permet de generer des nombres
  - `RandomGenerator`: Generateur alléatoire
  - `Ex9NumberGenerator`: Genère des nombres utilisé par l'exercice P9.

## Classes du Système

- `System` Le cœur de la simulation, contient tous les particules et l'enceinte et fait evoluer la simulation.
- `Enclosure`: Une enceinte qui définie les parois de la simulation.
- `Particle`: Represente une particule dans la simulation ayant une masse, vitesse et position, permette d'avoir des collisions et de mouvement.

  - `Argon`, `Helium`, `Neon`: Des particules differentes (sous-classes de particule)
  - `TraceParticle<TParticle>`: Particule permettant d'afficher le chemin parcouru du `TParticle` (qui peut être soit `Helium` soit `Neon` soit `Argon`)
    - `MotionTrace`: Collection des anciennes positions de `TraceParticle<TParticle>` qui peut être affiché

## Pour afficher

- `Drawable`: Un objet qui peut être dessiné sur un `DrawingFrame`
  - `Particle`
  - `MotionTrace`
  - `Enclosure`
  - `System`
- `DrawingFrame`: Un support sur lequel un `Drawable` peut dessiner
  - `TextViewer`: Permet d'afficher dans un text
  - `FileSaver`: Permet d'afficher dans un fichier
  - `OpenGLViewer`
- `Printable`: Implémente la méthode `vritual void print(std::ofstream &) const` et la méthode `virtual void printRaw(std::ofstream &) const` et peut être affiché en utilisant l'opérateur `<<`
  - `System`
  - `Vector`
  - `Particle`
  - `Enclosure`

## Classes pour le graphisme

- `MainWindow`: La fenêtre principale contenant `GLWidget`, `ControlsWidget` et `InfoWidget`
  - `ControlsWidget`: Le widget contenant des informations sur les touches et les contrôles
  - `InfoWidget`: Le widget contenant des informations sur la simulation
  - `GLWidget` Le widget qui execute la simulation et contrôle le `OpenGLViewer`
    - `OpenGLViewer` Un `DrawingFrame` qui permet d'afficher la simulation sur l'ecran
      - `Camera`: Contrôle la position et l'orientation de la caméra dans `OpenGLViewer`
      - `Light`: Contrôle la position, la couleur et les intensitées de la lumière utilisé par le "phong shader" dans `OpenGLViewer`
      - `GLSphere`: Permet de dessiner une sphère (ceci est une version modifié du tutoriel du graphisme)
