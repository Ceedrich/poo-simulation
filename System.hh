#pragma once
#include "Particle.hh"
#include "Enclosure.hh"
#include <vector>

class System
{
public:
       System() = default;
       System(double width, double length, double height)
           :space(width, length, height) {}
       void print(std::ostream&) const;
       void add_particle(Particle particle);
       void delete_particles();



private:
       Enclosure space;
       std::vector<Particle> elements;

};

std::ostream& operator<<(std::ostream &out, System const& system);
