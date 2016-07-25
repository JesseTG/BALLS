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
QT += core gui widgets

TARGET = BALLS
TEMPLATE = app

CONFIG += qt c++14 warn_on precompile_header qscintilla2
PRECOMPILED_HEADER = precompiled.hpp

DEFINES += \
  GLM_META_PROG_HELPERS \
  GENERATOR_USE_GLM \

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9
### </General Configuration> ###################################################

### <Source Files> #############################################################
SOURCES += \
  config/ProjectConfig.cpp \
  Constants.cpp \
  exception/FileException.cpp \
  exception/JsonException.cpp \
  gl/OpenGLPointers.cpp \
  main.cpp \
  model/gl/BlendState.cpp \
  model/gl/ClipOptions.cpp \
  model/gl/ColorOptions.cpp \
  model/gl/DepthOptions.cpp \
  model/gl/GeometryOptions.cpp \
  model/gl/Hints.cpp \
  model/gl/ImplementationInfo.cpp \
  model/gl/Limits.cpp \
  model/gl/SampleOptions.cpp \
  model/gl/StencilOptions.cpp \
  model/ImageTexture.cpp \
  model/mesh/BaseCylindricalMesh.cpp \
  model/mesh/BaseSphereMesh.cpp \
  model/mesh/BoxMesh.cpp \
  model/mesh/CapsuleMesh.cpp \
  model/mesh/ConeMesh.cpp \
  model/mesh/CylinderMesh.cpp \
  model/mesh/DiskMesh.cpp \
  model/Meshes.cpp \
  model/mesh/IcosahedronMesh.cpp \
  model/mesh/IcoSphereMesh.cpp \
  model/mesh/Mesh.cpp \
  model/mesh/MeshMesh.cpp \
  model/mesh/PlaneMesh.cpp \
  model/mesh/RoundedBoxMesh.cpp \
  model/mesh/SphereMesh.cpp \
  model/mesh/SphericalConeMesh.cpp \
  model/mesh/SphericalTriangleMesh.cpp \
  model/mesh/SpringMesh.cpp \
  model/mesh/TorusKnotMesh.cpp \
  model/mesh/TorusMesh.cpp \
  model/mesh/TriangleMesh.cpp \
  model/mesh/TubeMesh.cpp \
  model/OpenGLState.cpp \
  model/Texture.cpp \
  model/Uniforms.cpp \
  precompiled.cpp \
  shader/ShaderInputs.cpp \
  shader/ShaderUniform.cpp \
  ui/BallsCanvas.cpp \
  ui/BallsWindow.cpp \
  ui/docks/MeshManagerWidget.cpp \
  ui/docks/OpenGLStateWidget.cpp \
  ui/docks/TextureManager.cpp \
  ui/glslsyntax.cpp \
  ui/property/MatrixProperties.cpp \
  ui/property/MatrixProperty.cpp \
  ui/property/Vector2Property.cpp \
  ui/property/Vector3Property.cpp \
  ui/property/Vector4Property.cpp \
  ui/property/VectorProperty.cpp \
  ui/QsciLexerGLSL.cpp \
  util/AABB.cpp \
  util/ArcBall.cpp \
  util/ArcLookAt.cpp \
  util/Logging.cpp \
  util/MetaTypeConverters.cpp \
  util/TypeInfo.cpp \
  util/Util.cpp \

HEADERS  += \
  config/ProjectConfig.hpp \
  Constants.hpp \
  exception/FileException.hpp \
  exception/JsonException.hpp \
  gl/OpenGLPointers.hpp \
  model/gl/BlendState.hpp \
  model/gl/ClipOptions.hpp \
  model/gl/ColorOptions.hpp \
  model/gl/DepthOptions.hpp \
  model/gl/GeometryOptions.hpp \
  model/gl/Hints.hpp \
  model/gl/ImplementationInfo.hpp \
  model/gl/Limits.hpp \
  model/gl/SampleOptions.hpp \
  model/gl/StencilOptions.hpp \
  model/ImageTexture.hpp \
  model/mesh/BaseCylindricalMesh.hpp \
  model/mesh/BaseSphereMesh.hpp \
  model/mesh/BoxMesh.hpp \
  model/mesh/CapsuleMesh.hpp \
  model/mesh/ConeMesh.hpp \
  model/mesh/CylinderMesh.hpp \
  model/mesh/DiskMesh.hpp \
  model/Meshes.hpp \
  model/mesh/IcosahedronMesh.hpp \
  model/mesh/IcoSphereMesh.hpp \
  model/mesh/Mesh.hpp \
  model/mesh/MeshMesh.hpp \
  model/mesh/PlaneMesh.hpp \
  model/mesh/RoundedBoxMesh.hpp \
  model/mesh/SphereMesh.hpp \
  model/mesh/SphericalConeMesh.hpp \
  model/mesh/SphericalTriangleMesh.hpp \
  model/mesh/SpringMesh.hpp \
  model/mesh/TorusKnotMesh.hpp \
  model/mesh/TorusMesh.hpp \
  model/mesh/TriangleMesh.hpp \
  model/mesh/TubeMesh.hpp \
  model/OpenGLState.hpp \
  model/Texture.hpp \
  model/Uniforms.hpp \
  precompiled.hpp \
  shader/ShaderInputs.hpp \
  shader/ShaderUniform.hpp \
  ui/BallsCanvas.hpp \
  ui/BallsWindow.hpp \
  ui/docks/MeshManagerWidget.hpp \
  ui/docks/OpenGLStateWidget.hpp \
  ui/docks/TextureManager.hpp \
  ui/glslsyntax.hpp \
  ui/property/MatrixProperties.hpp \
  ui/property/MatrixProperty.hpp \
  ui/property/Vector2Property.hpp \
  ui/property/Vector3Property.hpp \
  ui/property/Vector4Property.hpp \
  ui/property/VectorProperty.hpp \
  ui/QsciLexerGLSL.h \
  util/AABB.hpp \
  util/ArcBall.hpp \
  util/ArcLookAt.hpp \
  util/Logging.hpp \
  util/MetaTypeConverters.hpp \
  util/TypeInfo.hpp \
  util/Util.hpp \

FORMS += \
  BallsWindow.ui \
  ui/docks/MeshManager.ui \
  ui/docks/OpenGLStateWidget.ui \
  ui/docks/TextureManager.ui \

RESOURCES += \
  resources.qrc

TRANSLATIONS += \
  text/BALLS_en.ts \
  text/BALLS_es.ts \

OTHER_FILES += \
  text/BALLS_es.ts \
  text/BALLS_en.ts \

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
      -O0 \
      -Wextra \
      -Wpedantic \
      -Wno-gnu-zero-variadic-macro-arguments \
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


DEPENDPATH += \
  $$DESTDIR \
  $$PWD/../QPropertyEditor \
  $$PWD/../Qtilities \


## Libraries to link
LIBS *= \
  -L$$DESTDIR \
  -lQPropertyEditor \
  -lqt5scintilla2 \
  -lgenerator-glm \

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

