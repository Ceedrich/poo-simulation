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

include(GNUInstallDirs)
