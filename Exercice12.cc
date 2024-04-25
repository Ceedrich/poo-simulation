#include "Graphics/GLWidget.hh"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  GLWidget window;

  window.show();

  return app.exec();
}
