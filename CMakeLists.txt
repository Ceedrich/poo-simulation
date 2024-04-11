cmake_minimum_required(VERSION 3.5)

project(poo-simulation LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

qt5_add_resources(RESOURCE_FILES Graphics/resources.qrc)

file(GLOB SOURCES_PARTICLES "Particles/*.cc")
file(GLOB HEADERS_PARTICLES "Particles/*.hh")

file(GLOB HEADERS_DRAWINGS "Drawings/*.hh")

file(GLOB SOURCES_NUMBER_GENERATORS "NumberGenerators/*.cc")
file(GLOB HEADERS_NUMBER_GENERATORS "NumberGenerators/*.hh")

file(GLOB SOURCES_GRAPHICS "Graphics/*.cc")
file(GLOB HEADERS_GRAPHICS "Graphics/*.hh")

file(GLOB SOURCES_TEXT "Text/*.cc")
file(GLOB HEADERS_TEXT "Text/*.hh")

# Tests
add_executable(Vector3D test_Vector3D.cc Vector3D.cc Vector3D.hh)
add_executable(Particle test_Particle.cc
    Particles/Particle.hh Particles/Particle.cc
    Particles/Neon.cc Particles/Neon.hh
    Vector3D.cc Vector3D.hh
)
add_executable(Enclosure test_Enclosure.cc Enclosure.hh Enclosure.cc)
add_executable(Exercice7 Exercice7.cc
    Enclosure.cc Enclosure.hh
    ${SOURCES_TEXT} ${HEADERS_TEXT}
    ${HEADERS_DRAWINGS}

    Vector3D.cc Vector3D.hh
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
)

add_executable(System test_System.cc
    System.cc System.hh
    ${SOURCES_DRAWINGS} ${HEADERS_DRAWINGS}
    Enclosure.cc Enclosure.hh
    Vector3D.cc Vector3D.hh

    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
)

add_executable(Exercice9 Exercice9.cc
    System.cc System.hh
    Enclosure.cc Enclosure.hh
    Vector3D.cc Vector3D.hh

    ${SOURCES_NUMBER_GENERATORS} ${HEADERS_NUMBER_GENERATORS}
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
)

add_executable(Graphisme graphisme.cc
    ${HEADERS_DRAWINGS}

    System.hh System.cc
    Enclosure.hh Enclosure.cc
    Vector3D.hh Vector3D.cc
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}

    ${SOURCES_GRAPHICS} ${HEADERS_GRAPHICS}

    ${RESOURCE_FILES}
)
target_link_libraries(Graphisme Qt5::Widgets OpenGL::GL)

include(GNUInstallDirs)
