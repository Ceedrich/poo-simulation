# POO: Simulation des particules

## Introduction
En principe, on a fait tout et aussi pas mal d'extensions. Pour la version graphique, on a utiliser Qt6.
TODO: combien d'heures par personne par semaine

Içi une liste des suppléments:
- TODO

## Structure du projet / comment rentrer
Pour compiler tous les executables (dans un dossier supplémentaire, il y'en a beacoup), exécuter ces commandes:
```sh
cmake -B bin -DCMAKE_BUILD_TYPE=Release
cmake --build bin --config Release
```
La compilation prendra environ une minute.

Ainsi, on trouve des executables de la forme "Exercice\*", "Test_\*" et l'executable principale "Simulation"

## Commandes clavier / souris

- <kbd>W</kbd>, <kbd>A</kbd>, <kbd>S</kbd>, <kbd>D</kbd>, <kbd>Space</kbd>, <kbd>Shift</kbd>: déplacer la caméra (avant, gauche, arrière, droite, haut, bas)
- <kbd>&larr;</kbd>, <kbd>&uarr;</kbd>, <kbd>&rarr;</kbd>, <kbd>&darr;</kbd>: modifier la rotation de la caméra (aussi avec la souris)
- <kbd>control</kbd>: augmenter la vitesse de la caméra
- <kbd>q</kbd>: sortir de la simulation
- <kbd>esc</kbd>: lancer/mettre en pause la simulation
- <kbd>return</kbd>: évoluer d'un pas la simulation
- <kbd>l</kbd>: déplacer la source de la lumière à sa position
- <kbd>r</kbd>: réinitialiser la position de la lumière et celle de la caméra.
- <kbd>7</kbd><kbd>8</kbd><kbd>9</kbd>: allumer/éteindre les trois parties de la lumiere "phong": "ambient", "diffuse", "specular"
- <kbd>P</kbd><kbd>I</kbd>: sauvegarder/charger l'état du système en un fichier (appelé `Simulation.csv`)
- <kbd>Z</kbd>: ralentir le mouvement des particules dans le système

## Remerciments
Merci beacoup à Valentina Frei pour la palette de couleurs pour les particules.


## Unitées:
1u = 0.1nm
