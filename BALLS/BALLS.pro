#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T13:31:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BALLS
TEMPLATE = app

CONFIG += c++11 warn_on
CONFIG(debug, debug|release): DEFINES += DEBUG
CONFIG(debug, debug|release): QMAKE_CXXFLAGS += -Wno-missing-braces
CONFIG(release, debug|release): DEFINES += NDEBUG
CONFIG(release, debug|release): QMAKE_CXXFLAGS += -Ofast -Wno-missing-braces

SOURCES += main.cpp\
        ui/BallsWindow.cpp \
    mesh/MeshFunction.cpp \
    ui/BallsCanvas.cpp \
    mesh/Mesh.cpp \
    mesh/MeshGenerator.cpp \
    mesh/Generators.cpp \
    ui/GLSLHighlighter.cpp \
    ui/GLSLPatterns.cpp \
    util/Util.cpp \
    mesh/ShaderInputs.cpp \
    config/Settings.cpp

HEADERS  += ui/BallsWindow.hpp \
    mesh/MeshFunction.hpp \
    ui/BallsCanvas.hpp \
    mesh/Mesh.hpp \
    mesh/MeshGenerator.hpp \
    mesh/MeshParameter.hpp \
    Constants.hpp \
    mesh/Generators.hpp \
    ui/GLSLHighlighter.hpp \
    ui/GLSLPatterns.hpp \
    util/Util.hpp \
    mesh/ShaderInputs.hpp \
    config/Settings.hpp

FORMS    += BallsWindow.ui

RESOURCES += \
    resources.qrc

QMAKE_RESOURCE_FLAGS += -compress 9 -threshold 1

OTHER_FILES += \
    shader/default.vert \
    shader/default.frag
