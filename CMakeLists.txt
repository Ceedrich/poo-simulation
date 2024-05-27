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
    Particles/MotionTrace.cc
    Particles/TraceParticle.cc
)
set(HEADERS_PARTICLES
    Particles/Particle.hh
    Particles/Helium.hh
    Particles/Neon.hh
    Particles/Argon.hh
    Particles/MotionTrace.hh
    Particles/TraceParticle.hh
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
    FileSaver/FileSaver.cc
)

set(HEADERS_GRAPHICS
    Graphics/Camera.hh
    Graphics/GLSphere.hh
    Graphics/GLWidget.hh
    Graphics/Inputs.hh
    Graphics/OpenGLViewer.hh
    Graphics/vertex_shader.hh
    Graphics/Light.hh
    Graphics/ControlsWidget.hh
    Graphics/InfoWidget.hh
    Graphics/MainWindow.hh
    FileSaver/FileSaver.hh
)

set(SOURCES_TEXT Text/TextViewer.cc)
set(HEADERS_TEXT Text/TextViewer.hh)

# Tests
add_executable(test_Vector3D Entrypoints/test_Vector3D.cc
    Vector3D.cc Vector3D.hh
    Printable.cc Printable.hh
)
add_executable(test_Particle Entrypoints/test_Particle.cc
    Particles/Particle.hh Particles/Particle.cc
    Particles/Neon.cc Particles/Neon.hh
    Vector3D.cc Vector3D.hh
    Printable.cc Printable.hh
)
add_executable(test_Enclosure Entrypoints/test_Enclosure.cc
    Enclosure.hh Enclosure.cc
    Printable.cc Printable.hh
)
add_executable(Exercice7 Entrypoints/Exercice7.cc
    Enclosure.cc Enclosure.hh
    ${SOURCES_TEXT} ${HEADERS_TEXT}
    ${HEADERS_DRAWINGS}

    Vector3D.cc Vector3D.hh
    Printable.cc Printable.hh
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
)

add_executable(test_System Entrypoints/test_System.cc
    System.cc System.hh
    ${SOURCES_DRAWINGS} ${HEADERS_DRAWINGS}
    Enclosure.cc Enclosure.hh
    Vector3D.cc Vector3D.hh
    Printable.cc Printable.hh

    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
)

add_executable(Exercice9 Entrypoints/Exercice9.cc
    System.cc System.hh
    Enclosure.cc Enclosure.hh
    Vector3D.cc Vector3D.hh
    Printable.cc Printable.hh

    ${HEADERS_NUMBER_GENERATORS}
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
)

add_executable(Exercice11 Entrypoints/Exercice11.cc
    ${HEADERS_DRAWINGS}

    System.hh System.cc
    Enclosure.hh Enclosure.cc
    Vector3D.hh Vector3D.cc
    Printable.hh Printable.cc
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}

    ${SOURCES_GRAPHICS} ${HEADERS_GRAPHICS}

    ${RESOURCE_FILES}
)
target_link_libraries(Exercice11 Qt5::Widgets OpenGL::GL)

add_executable(Exercice12 Entrypoints/Exercice12.cc
    ${HEADERS_DRAWINGS}

    System.hh System.cc
    Enclosure.hh Enclosure.cc
    Vector3D.hh Vector3D.cc
    Printable.hh Printable.cc
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
    Particles/TraceParticle.cc Particles/TraceParticle.hh
    Particles/MotionTrace.cc Particles/MotionTrace.hh

    ${SOURCES_GRAPHICS} ${HEADERS_GRAPHICS}

    ${RESOURCE_FILES}
)
target_link_libraries(Exercice12 Qt5::Widgets OpenGL::GL)

add_executable(Exercice13 Entrypoints/Exercice13.cc
    ${HEADERS_DRAWINGS}

    System.hh System.cc
    Enclosure.hh Enclosure.cc
    Vector3D.hh Vector3D.cc
    Printable.hh Printable.cc
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}
    Particles/TraceParticle.cc Particles/TraceParticle.hh
    Particles/MotionTrace.cc Particles/MotionTrace.hh

    ${SOURCES_GRAPHICS} ${HEADERS_GRAPHICS}

    ${RESOURCE_FILES}
)
target_link_libraries(Exercice13 Qt5::Widgets OpenGL::GL)

add_executable(Graphisme Entrypoints/graphisme.cc
    ${HEADERS_DRAWINGS}

    System.hh System.cc
    Enclosure.hh Enclosure.cc
    Vector3D.hh Vector3D.cc
    Printable.cc Printable.hh
    Particles/MotionTrace.cc Particles/MotionTrace.hh
    ${SOURCES_PARTICLES} ${HEADERS_PARTICLES}

    ${SOURCES_GRAPHICS} ${HEADERS_GRAPHICS}

    ${RESOURCE_FILES}
)
target_link_libraries(Graphisme Qt5::Widgets OpenGL::GL)



include(GNUInstallDirs)
