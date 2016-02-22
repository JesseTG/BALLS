include(../common.pri)

# BALLS Build Configuration File

### <User-Configurable Settings> ###############################################
!BALLS_TEMP_DIR {
  BALLS_TEMP_DIR = temp
}

# define UPX in the build process to compress the output with UPX
upx:!UPX_FLAGS {
  UPX_FLAGS = -7
}

upx:!UPX {
  UPX = upx
}
### </User-Configurable Settings> ##############################################


### <General Configuration> ####################################################
QT = core gui widgets
TARGET = BALLS
TEMPLATE = app

CONFIG += qt c++14 warn_on precompile_header qscintilla2
PRECOMPILED_HEADER = precompiled.hpp

DEFINES += \
  GLM_META_PROG_HELPERS

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9
### </General Configuration> ###################################################

### <Source Files> #############################################################
SOURCES += \
  main.cpp \
  ui/BallsWindow.cpp \
  mesh/MeshFunction.cpp \
  ui/BallsCanvas.cpp \
  mesh/Mesh.cpp \
  mesh/MeshGenerator.cpp \
  mesh/Generators.cpp \
  util/Util.cpp \
  config/Settings.cpp \
  ui/glslsyntax.cpp \
  Constants.cpp \
  shader/ShaderInputs.cpp \
  config/ProjectConfig.cpp \
  ui/docks/SceneSettings.cpp \
  ui/docks/OpenGLInfo.cpp \
  shader/ShaderUniform.cpp \
  ui/property/Vector2Property.cpp \
  ui/property/VectorProperty.cpp \
  precompiled.cpp \
  ui/property/Vector3Property.cpp \
  ui/property/Vector4Property.cpp \
  exception/FileException.cpp \
  exception/JsonException.cpp \
  util/Logging.cpp \
  ui/property/MatrixProperty.cpp \
  shader/syntax/GLSLSyntax.cpp \
  util/Trackball.cpp \
  util/MetaTypeConverters.cpp \
  ui/Uniforms.cpp \
  util/TypeInfo.cpp \
  ui/QsciLexerGLSL.cpp \
  ui/property/MatrixProperties.cpp \

HEADERS  += \
  precompiled.hpp \
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
  shader/ShaderInputs.hpp \
  shader/ShaderUniform.hpp \
  config/ProjectConfig.hpp \
  ui/docks/SceneSettings.hpp \
  ui/docks/OpenGLInfo.hpp \
  ui/property/Vector2Property.hpp \
  ui/property/VectorProperty.hpp \
  ui/property/Vector3Property.hpp \
  ui/property/Vector4Property.hpp \
  exception/FileException.hpp \
  exception/JsonException.hpp \
  util/Logging.hpp \
  ui/property/MatrixProperty.hpp \
  shader/syntax/GLSLSyntax.hpp \
  ui/QsciLexerGLSL.h \
  util/Trackball.hpp \
  ui/property/SamplerProperty.hpp \
  util/MetaTypeConverters.hpp \
  util/TypeInfo.hpp \
  ui/Uniforms.hpp \
  ui/property/MatrixProperties.hpp \

FORMS += \
  BallsWindow.ui \
  ui/docks/SceneSettings.ui \
  ui/docks/OpenGLInfo.ui \

RESOURCES += \
  resources.qrc

TRANSLATIONS += \
  text/BALLS_en.ts \
  text/BALLS_es.ts

OTHER_FILES += \
  shader/default.vert \
  shader/default.frag \
  glsl/phong.frag \
  ../.travis.yml \
  ../.gitignore \
  ../README.md \
  bar-descriptor.xml \
  text/BALLS_es.ts \
  text/BALLS_en.ts
### </Source Files> ############################################################

### <Compiler Flags> ###########################################################
warn_on {
  clang|gcc {
    QMAKE_CXXFLAGS_WARN_ON += \
      -Wno-missing-braces \
      -Wno-switch \
      -Wno-c++1y-extensions
  }
}

CONFIG(debug, debug|release) {
  DEFINES += DEBUG

  gcc|clang {
    QMAKE_CXXFLAGS_DEBUG += \
      -O0
  }

  clang {
    QMAKE_LFLAGS_DEBUG += \
#			-fsanitize-blacklist=$$PWD/balls.san \
#			-fsanitize=address \
#			-fsanitize=undefined \
      -ftemplate-backtrace-limit=0 \
#			-fsanitize=integer \
  }
}
else:CONFIG(release, debug|release) {
  DEFINES += NDEBUG QT_NO_DEBUG_OUTPUT QT_NO_DEBUG

  gcc|clang {
    QMAKE_CXXFLAGS_RELEASE += -Ofast
    QMAKE_LFLAGS_RELEASE += -Ofast
  }
}
### </Compiler Flags> ##########################################################

### <Includes and Dependencies> ################################################

INCLUDEPATH += \
  $$PWD/../ \
  $$PWD/../QPropertyEditor \
  /usr/include \
  /usr/local/include \
  /usr/include/x86_64-linux-gnu \
  /usr/include/x86_64-linux-gnu/qt5 \
  /usr/include/qt5 \


DEPENDPATH += \
  $$DESTDIR \
  $$PWD/../QPropertyEditor \
  $$PWD/../Qtilities


## Libraries to link
LIBS *= \
  -L$$DESTDIR \
  -L/usr/lib \
  -L/usr/local/lib \
  -L/usr/local/clang-3.5.0/lib \
  -L/usr/local/clang-3.6.0/lib \
  -L/usr/local/clang-3.7.0/lib \
  -L/usr/local/clang-3.8.0/lib \
  -L/usr/lib/x86_64-linux-gnu \
  -lQPropertyEditor \
  -lqt5scintilla2 \

## /Libraries to link

## Dependencies
win32-g++ {
  PRE_TARGETDEPS += $$DESTDIR/libQPropertyEditor.a
}
else:win32:!win32-g++ {
  PRE_TARGETDEPS += $$DESTDIR/QPropertyEditor.lib
}
else:unix {
  PRE_TARGETDEPS += $$DESTDIR/libQPropertyEditor.a
}
else {
  warning("What the hell are you building this thing on?")
}
## /Dependencies

### </Includes and Dependencies> ###############################################

### <Pre/Post-Compilation> #####################################################
upx {
  message("Compressing $${TARGET} with UPX flags $${UPX_FLAGS}")
  system("$${UPX} $${UPX_FLAGS}") {
    message("upx compression succeeded")
  }
  else: {
    message("upx compression failed")
  }
}

### </Pre/Post-Compilation> ####################################################

