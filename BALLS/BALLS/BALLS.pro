# BALLS Build Configuration File

### <User-Configurable Settings> ###############################################
!BALLS_TEMP_DIR {
	BALLS_TEMP_DIR = temp
}

### </User-Configurable Settings> ##############################################


### <General Configuration> ####################################################
QT = core gui widgets
TARGET = BALLS
TEMPLATE = app

CONFIG += qt c++14 warn_on precompile_header qscintilla2
PRECOMPILED_HEADER = precompiled.hpp

OBJECTS_DIR = $${BALLS_TEMP_DIR}
MOC_DIR = $${BALLS_TEMP_DIR}
UI_DIR = $${BALLS_TEMP_DIR}
RCC_DIR = $${BALLS_TEMP_DIR}

DEFINES += \
	QTILITIES_PROPERTY_BROWSER \
	GLM_META_PROG_HELPERS

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
	DEFINES += USING_PCH
}

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9

CONFIG(debug, debug|release) {
	BUILD_TYPE = debug
}
else:CONFIG(release, debug|release) {
	BUILD_TYPE = release
}
else {
	warning("Unknown build type; defaulting to debug")
	BUILD_TYPE = debug
}

message("Building in $${BUILD_TYPE} mode")
message("TARGET: $${TARGET}")
message("CONFIG: $${CONFIG}")
message("Temp files to be stored in $${BALLS_TEMP_DIR}")
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
	ui/property/MatrixProperties.cpp

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
	util/Trackball.hpp \
	ui/property/SamplerProperty.hpp \
	util/MetaTypeConverters.hpp \
	util/TypeInfo.hpp \
	ui/Uniforms.hpp \
	ui/property/MatrixProperties.hpp

FORMS += \
	BallsWindow.ui \
	ui/docks/SceneSettings.ui \
	ui/docks/OpenGLInfo.ui

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
	text/BALLS_en.ts \
	balls.san
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
	DESTDIR = $$PWD/../build/Debug

	gcc|clang {
		QMAKE_CXXFLAGS_DEBUG += \
			-fsanitize=address \
			-fsanitize-blacklist=$$PWD/balls.san \
			-fsanitize=integer \
			-fsanitize=undefined \
			-ftemplate-backtrace-limit=0 \
			-O0
	}

	clang {
		QMAKE_LFLAGS_DEBUG += \
			-fsanitize=address \
			-fsanitize=undefined
	}
}

CONFIG(release, debug|release) {
	DEFINES += NDEBUG QT_NO_DEBUG_OUTPUT QT_NO_DEBUG
	DESTDIR = $$PWD/../build/Release

	gcc|clang {
		QMAKE_CXXFLAGS_RELEASE += -Ofast -flto
		QMAKE_LFLAGS_RELEASE += -flto
	}
}
### </Compiler Flags> ##########################################################

### <Includes and Dependencies> ################################################

INCLUDEPATH += \
	$$PWD/../external/glm \
	$$PWD/../external/Qtilities/include \
	$$PWD/../external/qt-solutions/qtpropertybrowser/src \
	$$PWD/../QPropertyEditor

DEPENDPATH += \
	$$files($$PWD/../external/Qtilities/*, true) \
	$$PWD/../QPropertyEditor

## Libraries to link
win32 {
	LIBS += -L$$OUT_PWD/../QPropertyEditor/$${BUILD_TYPE}/ -lQPropertyEditor
}
else:unix {
	LIBS += -L$$OUT_PWD/../QPropertyEditor/ -lQPropertyEditor
}
## /Libraries to link

## Dependencies
win32-g++ {
	PRE_TARGETDEPS += $$OUT_PWD/../QPropertyEditor/$${BUILD_TYPE}/libQPropertyEditor.a
}
else:win32:!win32-g++ {
	PRE_TARGETDEPS += $$OUT_PWD/../QPropertyEditor/$${BUILD_TYPE}/QPropertyEditor.lib
}
else:unix {
	PRE_TARGETDEPS += $$OUT_PWD/../QPropertyEditor/libQPropertyEditor.a
}
else {
	warning("What the hell are you building this thing on?")
}
## /Dependencies

### </Includes and Dependencies> ###############################################


