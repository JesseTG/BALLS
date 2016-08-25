include($$top_srcdir/common.pri)

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
  precompiled.cpp \

HEADERS = \
  QPropertyEditor/ColorCombo.h \
  QPropertyEditor/Property.h \
  QPropertyEditor/QPropertyEditorWidget.h \
  QPropertyEditor/QPropertyModel.h \
  QPropertyEditor/QVariantDelegate.h \
  QPropertyEditor/EnumProperty.h \
  precompiled.hpp \

PRECOMPILED_HEADER = precompiled.hpp

CONFIG(debug, debug|release) {
}

CONFIG(release, debug|release) {
  DEFINES += NDEBUG QT_NO_DEBUG QT_NO_DEBUG_OUTPUT
  QMAKE_CXXFLAGS_RELEASE += -Ofast
  QMAKE_LFLAGS_RELEASE += -Ofast
}

macx {
  CONFIG += x86 ppc
  QMAKE_LFLAGS += -mmacosx-version-min=10.4
}
