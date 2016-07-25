#-------------------------------------------------
#
# Project created by QtCreator 2015-07-26T13:16:53
#
#-------------------------------------------------

include($$top_srcdir/common.pri)

QT       += testlib
QT       -= gui

TARGET = tst_TestJSONConversionsTest
CONFIG   += console testcase c++14
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += \
  SRCDIR=\\\"$$PWD/\\\" \
  GLM_META_PROG_HELPERS

INCLUDEPATH += \
  $$top_srcdir/BALLS

SOURCES += \
  tst_TestJSONConversionsTest.cpp

OBJECTS += \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/MetaTypeConverters.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/precompiled.o
