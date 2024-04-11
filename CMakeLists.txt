cmake_minimum_required(VERSION 3.5)

project(poo-simulation LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(simulation simulation.cc Vector3D.hh Vector3D.cc)

# Tests
add_executable(Vector3D test_Vector3D.cc Vector3D.cc Vector3D.hh)
add_executable(Particle test_Particle.cc
    Particles/Particle.cc Particles/Particle.hh
    Particles/Neon.hh Particles/Neon.cc
    Vector3D.cc Vector3D.hh
)
add_executable(Enclosure test_Enclosure.cc Enclosure.hh Enclosure.cc)
add_executable(Exercice7 Exercice7.cc
    Enclosure.cc Enclosure.hh
    Text/TextViewer.cc Text/TextViewer.hh
    Drawings/Drawable.hh
    Drawings/DrawingFrame.hh

    Vector3D.cc Vector3D.hh
    Particles/Particle.cc Particles/Particle.hh
    Particles/Neon.cc Particles/Neon.hh
    Particles/Argon.cc Particles/Argon.hh
)

add_executable(System test_System.cc
    System.cc System.hh
    Particles/Particle.cc Particles/Particle.hh
    Enclosure.cc Enclosure.hh
    Vector3D.cc Vector3D.hh
    Particles/Argon.cc Particles/Argon.hh
    Particles/Helium.cc Particles/Helium.hh
    Particles/Neon.cc Particles/Neon.hh
)

add_executable(Exercice9 Exercice9.cc
    NumberGenerators/NumberGenerator.hh
    NumberGenerators/Ex9NumberGenerator.hh
    NumberGenerators/RandomGenerator.hh
    Particles/Particle.cc Particles/Particle.hh
    System.cc System.hh
    Enclosure.cc Enclosure.hh
    Vector3D.cc Vector3D.hh
    Particles/Argon.cc Particles/Argon.hh
    Particles/Neon.cc Particles/Neon.hh
    Particles/Helium.cc Particles/Helium.hh
)

include(GNUInstallDirs)
