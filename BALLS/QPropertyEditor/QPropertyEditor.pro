QT       += core gui widgets

TARGET = QPropertyEditor
TEMPLATE = lib
CONFIG += qt c++14 warn_on precompile_header staticlib

QMAKE_CXXFLAGS_WARN_ON += \
  -Wno-missing-braces \
  -Wno-switch \
  -Wno-c++1y-extensions

SOURCES = \
    QPropertyEditor/ColorCombo.cpp \
    QPropertyEditor/Property.cpp \
    QPropertyEditor/QPropertyEditorWidget.cpp \
    QPropertyEditor/QPropertyModel.cpp \
    QPropertyEditor/QVariantDelegate.cpp \
    QPropertyEditor/EnumProperty.cpp \
    precompiled.cpp

HEADERS = \
    QPropertyEditor/ColorCombo.h \
    QPropertyEditor/Property.h \
    QPropertyEditor/QPropertyEditorWidget.h \
    QPropertyEditor/QPropertyModel.h \
    QPropertyEditor/QVariantDelegate.h \
    QPropertyEditor/EnumProperty.h \
    precompiled.hpp

PRECOMPILED_HEADER = precompiled.hpp

OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp

CONFIG(debug, debug|release) {
}

CONFIG(release, debug|release) { 
  DEFINES += NDEBUG QT_NO_DEBUG QT_NO_DEBUG_OUTPUT
  QMAKE_CXXFLAGS_RELEASE += -Ofast
}



macx {
	CONFIG += x86 ppc
	QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.4u.sdk
	QMAKE_LFLAGS += -mmacosx-version-min=10.4
}
