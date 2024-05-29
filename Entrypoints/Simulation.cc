#include "../Graphics/MainWindow.hh"
#include <QApplication>

/*
 * ENCLOSURE DIMENSIONS
 *
 * Set the dimensions of the enclosure (1 unit corresponds to 0.1 nm).
 */
constexpr double DIMENSION_X = 50.0;
constexpr double DIMENSION_Y = 50.0;
constexpr double DIMENSION_Z = 50.0;

/*
 * ENCOUNTER METHOD
 *
 * Choose the method used to determine whether two particles are close enough to
 * each other to collide. This option is only effective, if
 * `EVOLVE_METHOD_SIMPLE` is set as well.
 *
 * If `ENCOUNTER_METHOD_PAVING` is set, the space is divided up into cubes of
 * side length `epsilon`. Particles are close enough if their centers of mass
 * are in the same cube.
 *
 * If `ENCOUNTER_METHOD_CENTER_OF_MASS` is set, two particles are close enough,
 * if the distance of their centers of mass is smaller than `epsilon`.
 *
 */
constexpr System::ENCOUNTER_METHOD encounterMethod = //
    System::ENCOUNTER_METHOD_PAVING;
//  System::ENCOUNTER_METHOD_CENTER_OF_MASS;

/*
 * EVOLVE METHOD
 *
 * Choose the method used to step forward a small time step dt.
 *
 * If `EVOLVE_METHOD_SIMPLE` is set, the `ENCOUNTER_METHOD` is used to make the
 * particles collide. This algorithm is of time complexity `O(n^2)`
 *
 * If `EVOLVE_METHOD_ADVANCED` is set, the `ENCOUNTER_METHOD_PAVING` is
 * automatically used. This algorithm is of time complexity `O(n)`
 *
 */
constexpr System::EVOLVE_METHOD evolveMethod = //
    System::EVOLVE_METHOD_ADVANCED;
//  System::EVOLVE_METHOD_SIMPLE;

/*
 * EPSILON
 *
 * Set an epsilon value used to determine if two particles are close enough to
 * each other.
 *
 */
constexpr double epsilon(1.0);
/*
 * TEMPERATURE
 *
 * Set a temperature value in K for the simulation to run in
 *
 */
constexpr double temperature(0.1);

/*
 * NUMBER OF PARTICLES
 *
 * Set the number of particles in the simulation
 *
 */
constexpr size_t number_of_particles(1000);

/*
 * GRAPHICS LEVEL
 *
 * Choose the graphics level of the simulation.
 *
 * The `GRAPHICS_LEVEL_HIGH` will use an advanced phong shader capable of giving
 * a 3D effect to the system. The individual parts of the phong shader (ambient,
 * diffuse and specular lighting) can be toggled by using the 7, 8 and 9 keys on
 * the keyboard.
 *
 * The `GRAPHICS_LEVEL_LOW` will
 * use a simple shader only capable of drawing simple two-dimensional circles.
 *
 */
constexpr OpenGLViewer::GRAPHICS_LEVEL graphicsLevel = //
    OpenGLViewer::GRAPHICS_LEVEL_HIGH;
//  OpenGLViewer::GRAPHICS_LEVEL_LOW;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  System s(DIMENSION_X, DIMENSION_Y, DIMENSION_Z, 432153141);
  s.setEncounterMethod(encounterMethod);
  s.setEvolveMethod(evolveMethod);
  s.setEpsilon(epsilon);
  s.setTemperature(temperature);

  s.fill(number_of_particles);
  s.makeTraceParticle(0);

  MainWindow window(std::move(s));
  window.scene().setGraphicsLevel(graphicsLevel);

  window.show();

  return app.exec();
}
