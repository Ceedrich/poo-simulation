#include "Graphics/GLWidget.hh"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  GLWidget window;

  std::cout << "Starting Simulation..." << std::endl;

  window.show();

  return app.exec();
}
