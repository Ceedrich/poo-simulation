#pragma once
#include "ControlsWidget.hh"
#include "GLWidget.hh"
#include <QWidget>

class MainWindow : public QWidget {
public:
  MainWindow(System &&s)
      : controls(CONTROLS, this), scene_(this, std::move(s)), layout(this) {
    init();
  }
  MainWindow() : controls(CONTROLS, this), scene_(this), layout(this) {
    init();
  }

  GLWidget &scene() { return scene_; }

private:
  void init() {
    // Setup controls
    controls.setBackgroundRole(QPalette::Dark);

    // Setup Main Window
    setMinimumSize(500, 500);
    setStyleSheet("background-color: #000;");
    setContentsMargins(0, 0, 0, 0);

    layout.addWidget(&scene_, 1);
    layout.addWidget(&controls);
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
      "Save/Load the current status to a file (not working for TraceParticle)"};
  ControlsWidget controls;
  GLWidget scene_;
  QVBoxLayout layout;
};
