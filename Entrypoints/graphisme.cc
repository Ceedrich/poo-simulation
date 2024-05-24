#include "../Graphics/MainWindow.hh"
#include <QApplication>



int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  System s;
  s.fill(100);

  MainWindow window(std::move(s));
  window.show();

  return app.exec();
}
