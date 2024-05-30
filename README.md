# POO: Simulation des particules

## Introduction

On a fait tous les exercices donnés (P1-P14, (P2) n'est pas dans le projet) et aussi pas mal d'extensions. Pour la version graphique, on a utiliser Qt5.
On a travaillé environ 3 heures en moyenne par personne par semaine.

Içi une liste des suppléments:

- Lumière (Phong Lighting)
- Posibilité de modifier la taille de l'enceinte
- Charger/sauvegarder la simulation depuis/vers un fichier
- Ralentir la simulation
- Afficher des informations sur le système sur l'ecran
- Avoir multiple façons de fair evoluer/rencontre le système/les particules
- Modifier les paramètres de la simulation

## Structure du projet / comment rentrer

Pour compiler tous les executables (dans un dossier supplémentaire, "bin" içi, il y'en a beacoup), exécuter ces commandes:

```sh
cmake -B bin -DCMAKE_BUILD_TYPE=Release
cmake --build bin --config Release
```

La compilation prendra environ une minute.

Ainsi, on trouve des executables de la forme "Exercice\*", "Test\_\*" et l'executable principale "Simulation". Pour les executer on peut utiliser cette commande:

### L'executable Principal

Dans le fichier de l'executable principal (`Entrypoints/Simulation.cc`), on trouve beacoups des options a modifier pour changer le fonctionnement du programme. Après d'avoir modifié le code dans `Entrypoints/Simulation.cc`, il faut re-compiler le programme comme ceci:

```sh
cmake --build bin --config Release --target Simulation
```

Les modifications qu'on peut faire sont les suivantes: Plus d'information sur les options se trouve dans le fichier lui-même.

- Changer la dimensions d'Enceinte: Changer les valeurs de `DIMENSION_X`, `DIMENSION_Y` et `DIMENSION_Z`
- Changer le méthode de rencontre entre les particules: décommenter/commenter les lignes suivant `encounterMethod`
- Changer le méthode d'evolution (Soit en $\Theta(n)$ soit en $\Theta(n^2)$): décommenter/commenter les lignes suivant `evolveMethod`
- Modifier le "epsilon" de la simulation: Changer la valeur de `epsilon`
- Modifier la temperature de la simulation: Changer la valeur de `temperature`
- Modifier la nombre des particules dans la simulation: Changer la valeur de `number_of_particles`
- Choisir le niveau du graphisme (soit simple sans lumière soit avec "Phong lighting"): décommenter/commenter les lignes suivant `graphicsLevel`

```sh
./bin/Simulation
```

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
