#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T13:31:00
#
#-------------------------------------------------

QT       += core gui widgets
TARGET = BALLS
TEMPLATE = app

QMAKE_CXXFLAGS_WARN_ON += \
	-Wno-missing-braces \
	-Wno-switch \
	-Wno-c++1y-extensions

CONFIG += qt c++14 warn_on precompile_header qscintilla2

CONFIG(debug, debug|release) {
	CONFIG += debug
	DEFINES += DEBUG
	QMAKE_CXXFLAGS_DEBUG += \
		-fsanitize=address \
		-fsanitize-blacklist=$$PWD/balls.san \
		-fsanitize=integer \
		-fsanitize=undefined \
		-ftemplate-backtrace-limit=0 \
		-O0

	QMAKE_LFLAGS_DEBUG += \
		-fsanitize=address \
		-fsanitize=undefined
}

CONFIG(release, debug|release) {
	DEFINES += NDEBUG QT_NO_DEBUG_OUTPUT QT_NO_DEBUG
	QMAKE_CXXFLAGS_RELEASE += -Ofast
}

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp
DEFINES += \
	GLM_META_PROG_HELPERS

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
		ui/glslsyntax.cpp \
		Constants.cpp \
		shader/ShaderInputs.cpp \
		config/ProjectConfig.cpp \
		ui/QsciLexerGLSL.cpp \
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
		shader/ShaderInputs.hpp \
		shader/ShaderUniform.hpp \
		config/ProjectConfig.hpp \
		ui/QsciLexerGLSL.h \
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

FORMS    += BallsWindow.ui \
		ui/docks/SceneSettings.ui \
		ui/docks/OpenGLInfo.ui

RESOURCES += \
		resources.qrc

TRANSLATIONS += \
	text/BALLS_en.ts \
	text/BALLS_es.ts

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QPropertyEditor/release/ -lQPropertyEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QPropertyEditor/debug/ -lQPropertyEditor
else:unix: LIBS += -L$$OUT_PWD/../QPropertyEditor/ -lQPropertyEditor

INCLUDEPATH += $$PWD/../QPropertyEditor
DEPENDPATH += $$PWD/../QPropertyEditor

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QPropertyEditor/release/libQPropertyEditor.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QPropertyEditor/debug/libQPropertyEditor.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QPropertyEditor/release/QPropertyEditor.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QPropertyEditor/debug/QPropertyEditor.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QPropertyEditor/libQPropertyEditor.a
