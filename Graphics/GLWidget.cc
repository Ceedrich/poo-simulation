#include "GLWidget.hh"
#include "../Particles/TraceParticle.hh"
#include "Inputs.hh"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTimerEvent>
#include <cmath>
#include <fstream>

using std::asin, std::clamp;

void GLWidget::initializeGL() {
  initCamera();
  initLight();
  viewer.init();

  timerID = startTimer(20);
  ctimerID = startTimer(20);
  pause();
}

void GLWidget::initCamera() {
  constexpr double CAMERA_OFFSET = 1.2;

  viewer.camera().setPosition(system.enclosure().width() * CAMERA_OFFSET,
                              system.enclosure().height() / 2,
                              system.enclosure().length() * CAMERA_OFFSET);

  viewer.camera().lookAt(system.enclosure().width() / 2,
                         system.enclosure().height() / 2,
                         system.enclosure().length() / 2);
}

void GLWidget::initLight() {
  constexpr double LIGHT_OFFSET = 1.4;

  viewer.light().setPosition(system.enclosure().width() * LIGHT_OFFSET,
                             system.enclosure().height() * LIGHT_OFFSET,
                             system.enclosure().length() * LIGHT_OFFSET);
}

void GLWidget::reset() {
  initCamera();
  initLight();
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);

  QMatrix4x4 matrix;
  matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3,
                     1e5);
  viewer.setProjection(matrix);
}

void GLWidget::paintGL() {
  viewer.updateShaderUniformValues();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  system.draw_on(viewer);
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Inputs::ROTATE_LEFT:
    keysPressed |= FLAGS::ROTATE_LEFT;
    break;
  case Inputs::ROTATE_RIGHT:
    keysPressed |= FLAGS::ROTATE_RIGHT;
    break;
  case Inputs::ROTATE_UP:
    keysPressed |= FLAGS::ROTATE_UP;
    break;
  case Inputs::ROTATE_DOWN:
    keysPressed |= FLAGS::ROTATE_DOWN;
    break;
  case Inputs::STRAVE_FORWARD:
    keysPressed |= FLAGS::STRAVE_FORWARD;
    break;
  case Inputs::STRAVE_BACKWARD:
    keysPressed |= FLAGS::STRAVE_BACKWARD;
    break;
  case Inputs::STRAVE_LEFT:
    keysPressed |= FLAGS::STRAVE_LEFT;
    break;
  case Inputs::STRAVE_RIGHT:
    keysPressed |= FLAGS::STRAVE_RIGHT;
    break;
  case Inputs::STRAVE_DOWN:
    keysPressed |= FLAGS::STRAVE_DOWN;
    break;
  case Inputs::STRAVE_UP:
    keysPressed |= FLAGS::STRAVE_UP;
    break;
  case Inputs::SPEED_MODIFIER:
    keysPressed |= FLAGS::SPEED_UP;
    break;
  case Inputs::PAUSE:
    pause();
    break;
  case Inputs::QUIT:
    if (parentWidget() != nullptr)
      parentWidget()->close();
    else {
      close();
    }
    break;
  case Inputs::EVOLVE:
    system.evolve(dt);
    update();
    break;
  case Inputs::MOVE_LIGHT_SOURCE:
    viewer.light().setPosition(viewer.camera().position());
    update();
    break;
  case Inputs::TOGGLE_AMBIENT:
    viewer.light().toggleAmbient();
    break;
  case Inputs::TOGGLE_DIFFUSE:
    viewer.light().toggleDiffuse();
    break;
  case Inputs::TOGGLE_SPECULAR:
    viewer.light().toggleSpecular();
    break;
  case Inputs::RESET_VIEW:
    reset();
    break;
  case Inputs::SAVE_FILE:
    saveToFile();
    break;
  case Inputs::LOAD_FILE:
    loadFromFile();
    break;
  case Inputs::SLOW_DOWN_SIMULATION:
    slowDown = !slowDown;
    break;
  case Inputs::REDUCE_ENCLOSURE_SIZE:
    system.reduceEnclosure();
    break;
  case Inputs::AUGMENT_ENCLOSURE_SIZE:
    system.augmentEnclosure();
    break;
  }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Inputs::ROTATE_LEFT:
    keysPressed &= ~FLAGS::ROTATE_LEFT;
    break;
  case Inputs::ROTATE_RIGHT:
    keysPressed &= ~FLAGS::ROTATE_RIGHT;
    break;
  case Inputs::ROTATE_UP:
    keysPressed &= ~FLAGS::ROTATE_UP;
    break;
  case Inputs::ROTATE_DOWN:
    keysPressed &= ~FLAGS::ROTATE_DOWN;
    break;
  case Inputs::STRAVE_FORWARD:
    keysPressed &= ~FLAGS::STRAVE_FORWARD;
    break;
  case Inputs::STRAVE_BACKWARD:
    keysPressed &= ~FLAGS::STRAVE_BACKWARD;
    break;
  case Inputs::STRAVE_LEFT:
    keysPressed &= ~FLAGS::STRAVE_LEFT;
    break;
  case Inputs::STRAVE_RIGHT:
    keysPressed &= ~FLAGS::STRAVE_RIGHT;
    break;
  case Inputs::STRAVE_DOWN:
    keysPressed &= ~FLAGS::STRAVE_DOWN;
    break;
  case Inputs::STRAVE_UP:
    keysPressed &= ~FLAGS::STRAVE_UP;
    break;
  case Inputs::SPEED_MODIFIER:
    keysPressed &= ~FLAGS::SPEED_UP;
    break;
  }
}

void GLWidget::timerEvent(QTimerEvent *event) {
  if (event->timerId() == timerID) {
    updateSystemTimer();
  }
  if (event->timerId() == ctimerID) {
    updateCameraTimer();
  }
  update();
}

void GLWidget::updateSystemTimer() {
  double dt =
      stopwatch.restart() / 1000.0 * (slowDown ? slowDownMultiplier : 1.0);

  system.evolve(dt);
}
void GLWidget::updateCameraTimer() {
  constexpr double panSpeed(0.6);
  double dt = cstopwatch.restart() / 1000.0;
  if (!keysPressed) {
    return;
  }

  if (keysPressed & FLAGS::ROTATE_LEFT)
    viewer.camera().rotateYaw(+panSpeed * dt);
  if (keysPressed & FLAGS::ROTATE_RIGHT)
    viewer.camera().rotateYaw(-panSpeed * dt);
  if (keysPressed & FLAGS::ROTATE_UP)
    viewer.camera().rotatePitch(+panSpeed * dt);
  if (keysPressed & FLAGS::ROTATE_DOWN)
    viewer.camera().rotatePitch(-panSpeed * dt);

  const double speed =
      cMovementSpeed * (keysPressed & FLAGS::SPEED_UP ? cSpeedMultiplier : 1);

  if (keysPressed & FLAGS::STRAVE_FORWARD)
    viewer.camera().move(0.0, 0.0, +speed * dt);
  if (keysPressed & FLAGS::STRAVE_BACKWARD)
    viewer.camera().move(0.0, 0.0, -speed * dt);
  if (keysPressed & FLAGS::STRAVE_UP)
    viewer.camera().move(0.0, +speed * dt, 0.0);
  if (keysPressed & FLAGS::STRAVE_DOWN)
    viewer.camera().move(0.0, -speed * dt, 0.0);
  if (keysPressed & FLAGS::STRAVE_LEFT)
    viewer.camera().move(+speed * dt, 0.0, 0.0);
  if (keysPressed & FLAGS::STRAVE_RIGHT)
    viewer.camera().move(-speed * dt, 0.0, 0.0);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  lastMousePosition = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  double constexpr smallAngle(0.4 / 180);
  if (event->buttons() & Qt::LeftButton) {
    double dx(event->pos().x() - lastMousePosition.x());
    double dy(event->pos().y() - lastMousePosition.y());

    lastMousePosition = event->pos();

    viewer.camera().rotateYaw(dx * smallAngle);
    viewer.camera().rotatePitch(dy * smallAngle);

    update();
  }
}

void GLWidget::pause() {
  if (timerID == 0) {
    timerID = startTimer(20);
    stopwatch.restart();
  } else {
    killTimer(timerID);
    timerID = 0;
  }
}

constexpr auto SAVE_FILE_NAME = "Simulation.csv";
void GLWidget::saveToFile() {
  FileSaver saver(SAVE_FILE_NAME);
  system.draw_on(saver);
}

void GLWidget::loadFromFile() {
  std::ifstream file(SAVE_FILE_NAME);
  std::string delimiter;
  double epsilon, temperature;
  int encounterMethod, evolveMethod;
  double w, h, l;
  file >> delimiter;
  file >> epsilon >> temperature;
  file >> evolveMethod >> encounterMethod;
  file >> w >> h >> l;
  System s(w, h, l);
  s.setEpsilon(epsilon);
  s.setTemperature(temperature);
  s.setEncounterMethod((System::ENCOUNTER_METHOD)encounterMethod);
  s.setEvolveMethod((System::EVOLVE_METHOD)evolveMethod);
  while (!file.fail() && !file.eof()) {
    std::string delimiter;
    if (delimiter == "M") {
      // discard Trace
      getline(file, delimiter);
      continue;
    }
    double rx, ry, rz, vx, vy, vz, m;
    file >> delimiter >> rx >> ry >> rz >> vx >> vy >> vz >> m;
    if (delimiter == "Helium") {
      s.add_particle(Helium(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "Neon") {
      s.add_particle(Neon(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "Argon") {
      s.add_particle(Argon(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "TraceHelium") {
      s.add_particle(
          TraceParticle<Helium>(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "TraceNeon") {
      s.add_particle(
          TraceParticle<Neon>(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
    if (delimiter == "TraceArgon") {
      s.add_particle(
          TraceParticle<Argon>(Vector3D(rx, ry, rz), Vector3D(vx, vy, vz), m));
    }
  }

  system = std::move(s);
  initCamera();
  initLight();
  cMovementSpeed =
      std::max({system.enclosure().width(), system.enclosure().height(),
                system.enclosure().length()});
}

System::Info GLWidget::systemInfo() const {
  return {
      .averageKineticEnergy = system.averageKineticEnergy(),
      .epsilon = system.epsilon(),
      .temperature = system.temperature(),
  };
}
