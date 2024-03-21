cmake_minimum_required(VERSION 3.5)

project(poo-simulation LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(simulation main.cc Vector3D.hh Vector3D.cc)

# Tests
add_executable(Vector3D test_Vector3D.cc Vector3D.cc Vector3D.hh)
add_executable(Particle
    test_Particle.cc Particle.cc Particle.hh
    Vector3D.cc Vector3D.hh
)
add_executable(Enclosure test_Enclosure.cc Enclosure.hh Enclosure.cc)
add_executable(Exercice7 Exercice7.cc
    Enclosure.cc Enclosure.hh
    TextViewer.cc TextViewer.hh
    Drawable.hh
    DrawingFrame.hh

    Vector3D.cc Vector3D.hh
    Particle.cc Particle.hh
    Neon.cc Neon.hh
    Argon.cc Argon.hh
)

add_executable(System test_System.cc System.cc System.hh
    Particle.cc Particle.hh
    Enclosure.cc Enclosure.hh
    Vector3D.cc Vector3D.hh
    Argon.cc Argon.hh
    Helium.cc Helium.hh
    Neon.cc Neon.hh
)

include(GNUInstallDirs)
