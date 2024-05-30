#pragma once
#include <QGridLayout>
#include <QLabel>
#include <QWidget>

class InfoWidget : public QWidget {
public:
  InfoWidget(QWidget *parent = nullptr)
      : QWidget(parent), layout(this),                //
        epsilonLabel("Epsilon"),                      //
        temperatureLabel("Temperature"),              //
        kineticEnergyLabel("Average Kinetic Energy"), //
        particleCollisionsLabel(
            "Average collisions between particles per time"), //
        enclosureCollisionsLabel(
            "Average collisions with enclosure per time"), //
        noParticlesLabel("Number of particles") {

    layout.setSpacing(5);

    setStyleSheet("background-color: transparent;");
    setAttribute(Qt::WA_TransparentForMouseEvents);

    layout.addWidget(&noParticlesLabel, 0, 0);
    layout.addWidget(&noParticles_, 0, 1);
    layout.addWidget(&epsilonLabel, 1, 0);
    layout.addWidget(&epsilon_, 1, 1);
    layout.addWidget(&temperatureLabel, 2, 0);
    layout.addWidget(&temperature_, 2, 1);
    layout.addWidget(&kineticEnergyLabel, 3, 0);
    layout.addWidget(&kineticEnergy_, 3, 1);
    layout.addWidget(&enclosureCollisionsLabel, 4, 0);
    layout.addWidget(&enclosureCollisions_, 4, 1);
    layout.addWidget(&particleCollisionsLabel, 5, 0);
    layout.addWidget(&particleCollisions_, 5, 1);

    layout.setColumnStretch(0, 0);
    layout.setColumnStretch(1, 1);

    layout.setVerticalSpacing(0);
  }

  void setEpsilon(double epsilon) {
    epsilon_.setText(std::to_string(epsilon).c_str());
  }
  void setTemperature(double temp) {
    temperature_.setText(std::to_string(temp).c_str());
  }
  void setAverageKineticEnergy(double kinE) {
    kineticEnergy_.setText(std::to_string(kinE).c_str());
  }
  void setParticleCollisions(double cols) {
    particleCollisions_.setText(std::to_string(cols).c_str());
  }
  void setEnclosureCollisions(double cols) {
    enclosureCollisions_.setText(std::to_string(cols).c_str());
  }
  void setNumberOfParticles(size_t n) {
    noParticles_.setText(std::to_string(n).c_str());
  }

private:
  QGridLayout layout;
  QLabel epsilonLabel, epsilon_,                      //
      temperatureLabel, temperature_,                 //
      kineticEnergyLabel, kineticEnergy_,             //
      particleCollisionsLabel, particleCollisions_,   //
      enclosureCollisionsLabel, enclosureCollisions_, //
      noParticlesLabel, noParticles_;                 //
};
