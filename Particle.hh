#pragma once

#include "Vector3D.hh"
#include <iostream>

class Particle
{
public:
    Particle(Vector3D pos, Vector3D v, double m) : position(pos), speed(v), mass(m) {}
    void print(std::ostream& out) const;
private:
    Vector3D position;
    Vector3D speed;
    double mass;
};

std::ostream& operator<<(std::ostream& out, Particle element);
