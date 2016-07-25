include($$top_srcdir/common.pri)

QT       += widgets testlib

TARGET = tst_TestConversions
CONFIG   += testcase console c++14
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += \
  $$top_srcdir/BALLS

SOURCES += \
  tst_TestConversions.cpp

OBJECTS += \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/MetaTypeConverters.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/precompiled.o

DEFINES += \
  SRCDIR=\\\"$$PWD/\\\" \
