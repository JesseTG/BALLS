#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T13:31:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BALLS
TEMPLATE = app

CONFIG += c++11 warn_on precompile_header autogen_precompile_source
CONFIG(debug, debug|release): DEFINES += DEBUG
CONFIG(debug, debug|release): QMAKE_CXXFLAGS += -Wno-missing-braces
CONFIG(release, debug|release): DEFINES += NDEBUG
CONFIG(release, debug|release): QMAKE_CXXFLAGS += -Ofast -Wno-missing-braces
precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp

PRECOMPILED_HEADER = precompiled.hpp

SOURCES += main.cpp\
        ui/BallsWindow.cpp \
    mesh/MeshFunction.cpp \
    ui/BallsCanvas.cpp \
    mesh/Mesh.cpp \
    mesh/MeshGenerator.cpp \
    mesh/Generators.cpp \
    util/Util.cpp \
    config/Settings.cpp \
    ui/glslhighlighter.cpp \
    ui/glslsyntax.cpp \
    Constants.cpp \
    shader/ShaderInputs.cpp \
    ui/BallsCanvasUniformInitializers.cpp \
    ui/UniformWidget.cpp \
    config/ProjectConfig.cpp \
    ui/VectorWidget.cpp

HEADERS  += precompiled.hpp \
    ui/BallsWindow.hpp \
    mesh/MeshFunction.hpp \
    ui/BallsCanvas.hpp \
    mesh/Mesh.hpp \
    mesh/MeshGenerator.hpp \
    mesh/MeshParameter.hpp \
    Constants.hpp \
    mesh/Generators.hpp \
    util/Util.hpp \
    config/Settings.hpp \
    ui/glslsyntax.hpp \
    ui/glslhighlighter.hpp \
    shader/ShaderInputs.hpp \
    shader/ShaderUniform.hpp \
    ui/UniformWidget.hpp \
    config/ProjectConfig.hpp \
    ui/VectorWidget.hpp

FORMS    += BallsWindow.ui

RESOURCES += \
    resources.qrc

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9
OTHER_FILES += \
    shader/default.vert \
    shader/default.frag \
    glsl/phong.frag \
    ../.travis.yml \
    ../.gitignore \
    ../README.md
