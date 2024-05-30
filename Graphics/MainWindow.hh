#pragma once
#include "ControlsWidget.hh"
#include "GLWidget.hh"
#include "InfoWidget.hh"
#include <QTimer>
#include <QWidget>

class MainWindow : public QWidget {
public:
  MainWindow(System &&s)
      : controls(CONTROLS, this), scene_(this, std::move(s)), mainLayout(this) {
    init();
  }
  MainWindow() : controls(CONTROLS, this), scene_(this), mainLayout(this) {
    init();
  }

  GLWidget &scene() { return scene_; }

private:
  QTimer timer;
  int timerID;

  virtual void timerEvent(QTimerEvent *event) override {
    if (event->timerId() == timerID) {
      updateSystemInfo();
    }
  }
  void init() {
    timerID = startTimer(100);
    // Setup Text Widgets
    controls.setBackgroundRole(QPalette::Dark);
    info.setBackgroundRole(QPalette::Dark);

    // Setup Main Window
    setMinimumSize(500, 500);
    setStyleSheet("background-color: #000;");
    setContentsMargins(0, 0, 0, 0);

    updateSystemInfo();

    mainLayout.addWidget(&scene_, 1);
    bottomLayout.addWidget(&controls, 1);
    bottomLayout.addWidget(&info, 1);

    mainLayout.addLayout(&bottomLayout);
  }

  void updateSystemInfo() {
    auto systemInfo(scene().systemInfo());
    info.setEpsilon(systemInfo.epsilon);
    info.setTemperature(systemInfo.temperature);
    info.setAverageKineticEnergy(systemInfo.averageKineticEnergy);
    info.setEnclosureCollisions(systemInfo.enclosureCollisionsPerTime);
    info.setParticleCollisions(systemInfo.particleCollisionsPerTime);
  }

  static auto constexpr CONTROLS = {
      "W, A, S, D, SPACE, SHIFT",
      "move camera", //
      "CTRL",
      "hold to increase moving speed", //
      "(arrow keys), (mouse)",
      "look around", //
      "ESC",
      "play/pause simulation", //
      "Q",
      "quit the simulation", //
      "RETURN",
      "evolve one step (dt)", //
      "L",
      "move light source to current position", //
      "R",
      "reset camera and light position", //
      "7,8,9",
      "toggle ambient, diffuse and specular lighting", //
      "P, I",
      "Save/Load the current status to a file", //
      "Z",
      "Slow down the simulation", //
      "N, M",
      "Reduce/Augment the size of the enclosure", //
  };
  ControlsWidget controls;
  InfoWidget info;
  GLWidget scene_;
  QVBoxLayout mainLayout;
  QHBoxLayout bottomLayout;
};
