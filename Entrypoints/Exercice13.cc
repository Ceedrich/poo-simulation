#include "../Graphics/GLWidget.hh"
#include "../Particles/TraceParticle.hh"
#include "../System.hh"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  System s(System::prefilled());
  s.add_particle(TraceParticle(Vector3D(14.5, 17.1, 5.0),
                               Vector3D(13.827, 6.09123, 23.2392), 1.0));
  GLWidget window(std::move(s));

  window.show();

  return app.exec();
}
