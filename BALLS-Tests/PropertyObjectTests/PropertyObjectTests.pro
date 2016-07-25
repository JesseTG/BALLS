#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T22:55:59
#
#-------------------------------------------------
include($$top_srcdir/common.pri)

QT       += core gui widgets testlib

TARGET = tst_PropertyObjectTests
CONFIG   += console testcase c++14
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
  tst_PropertyObjectTests.cpp \

DEFINES += \
  SRCDIR=\\\"$$PWD/\\\" \
  GLM_META_PROG_HELPERS \

INCLUDEPATH += \
  $$top_srcdir/BALLS \
  $$top_srcdir/QPropertyEditor

LIBS += \
  -L$$top_builddir/QPropertyEditor \
  -lQPropertyEditor

OBJECTS += \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/Vector2Property.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/moc_Vector2Property.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/Vector3Property.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/moc_Vector3Property.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/Vector4Property.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/moc_Vector4Property.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/VectorProperty.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/MatrixProperty.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/MatrixProperties.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/moc_MatrixProperties.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/TypeInfo.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/Constants.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/precompiled.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/MetaTypeConverters.o \
