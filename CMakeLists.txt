cmake_minimum_required(VERSION 3.5)

project(poo-simulation LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE GLVND) # Don't use legacy libraries

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

qt5_add_resources(RESOURCE_FILES Graphics/resources.qrc)

set(SOURCES_PARTICLES
    Particles/Particle.cc
    Particles/Helium.cc
    Particles/Neon.cc
    Particles/Argon.cc
)
set(HEADERS_PARTICLES
    Particles/Particle.hh
    Particles/Helium.hh
    Particles/Neon.hh
    Particles/Argon.hh
)

set(HEADERS_DRAWINGS
    Drawings/Drawable.hh
    Drawings/DrawingFrame.hh
)

set(HEADERS_NUMBER_GENERATORS
    NumberGenerators/NumberGenerator.hh
    NumberGenerators/RandomGenerator.hh
    NumberGenerators/Ex9NumberGenerator.hh
)

set(SOURCES_GRAPHICS
    Graphics/Camera.cc
    Graphics/GLSphere.cc
    Graphics/GLWidget.cc
    Graphics/OpenGLViewer.cc
)

set(HEADERS_GRAPHICS
    Graphics/Camera.hh
    Graphics/GLSphere.hh
    Graphics/GLWidget.hh
    Graphics/Inputs.hh
    Graphics/OpenGLViewer.hh
    Graphics/vertex_shader.hh
    Graphics/Light.hh
)

set(SOURCES_TEXT Text/TextViewer.cc)
set(HEADERS_TEXT Text/TextViewer.hh)

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

    ${HEADERS_NUMBER_GENERATORS}
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

add_executable(Exercice12 Exercice12.cc
    ${HEADERS_DRAWINGS}

    System.hh System.cc
    Enclosure.hh Enclosure.cc
    Vector3D.hh Vector3D.cc
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}

    ${SOURCES_GRAPHICS} ${HEADERS_GRAPHICS}

    ${RESOURCE_FILES}
)
target_link_libraries(Exercice12 Qt5::Widgets OpenGL::GL)

add_executable(Exercice13 Exercice13.cc
    ${HEADERS_DRAWINGS}

    System.hh System.cc
    Enclosure.hh Enclosure.cc
    Vector3D.hh Vector3D.cc
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
    Particles/TraceParticle.cc Particles/TraceParticle.hh
    Particles/MotionTrace.cc Particles/MotionTrace.hh

    ${SOURCES_GRAPHICS} ${HEADERS_GRAPHICS}

    ${RESOURCE_FILES}
)
target_link_libraries(Exercice13 Qt5::Widgets OpenGL::GL)


include(GNUInstallDirs)
