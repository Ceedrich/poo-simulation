#include "Graphics/ControlsWidget.hh"
#include "Graphics/GLWidget.hh"
#include "Graphics/MainWindow.hh"
#include "Graphics/OpenGLViewer.hh"
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <array>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  System s;
  s.fill(100);

  MainWindow window(std::move(s));
  window.scene().setShaderMode(OpenGLViewer::SHADER_MODE_MINIMAL);
  window.show();

  return app.exec();
}
