#include "../Graphics/MainWindow.hh"
#include "../Particles/TraceParticle.hh"
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  System s;
  // s.fill(100);

  s.add_particle(TraceParticle(Vector3D(), Vector3D(4.0, 1.0, 7.0), 10.0));

  MainWindow window(std::move(s));
  window.show();

  return app.exec();
}
