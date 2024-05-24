#include "../Graphics/GLWidget.hh"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  System s(System::exercice9());

  GLWidget window(std::move(s));

  window.show();

  return app.exec();
}
