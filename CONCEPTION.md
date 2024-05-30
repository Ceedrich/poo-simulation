# Conceptions

## Classes de base
- `Vector3D`: represente un vecteur en 3D au sens physique et permet quelques opérations de base.
- `Particle`: represente une particule dans la simulation ayant une masse, vitesse et position, permette d'avoir des collisions
- `System`: Le cœur de la simulation, contient tous les particules et fait evoluer la simulation.
- `Enclosure`: Une enceinte qui définie les bords de la simulation
- `Argon`, `Helium`, `Neon`: des particules differentes (héritent de la super-classe `Particle`)
- `RandomGenerator`
- `MotionTrace`
- `Filesaver`
- `TraceParticle`

## Classes abstraites
- `Drawable`: Un objet qui peut être dessiné sur un `DrawingFrame`. Les objets suivantes sont des `Drawable`:
  - `Particle`
  - `Enclosure`
- `DrawingFrame`: Un support sur lequel un `Drawable` peut dessiner. Les objets suivantes son des `DrawingFrame`
  - `TextViewer`
  - `NumberGenerator`
- `Printable`
- 

## Classes Graphics
- `Camera`
- `QWidget`
- `ControlsWidget`
- `GLSphere`
- `GLWidget`
- `QOpenGLWidget`
- `InfoWidget`
- `Light`
- `MainWindow`
- `OpenGLViewer`
- //Drawing frame?, Textviewer
- 


