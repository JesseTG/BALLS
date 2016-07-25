include($$top_srcdir/common.pri)

QT       += testlib
QT       -= gui

TARGET = tst_TestJSONConversionsTest
CONFIG   += console testcase c++14
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += \
  SRCDIR=\\\"$$PWD/\\\" \

INCLUDEPATH += \
  $$top_srcdir/BALLS

SOURCES += \
  tst_TestJSONConversionsTest.cpp

OBJECTS += \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/MetaTypeConverters.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/precompiled.o
