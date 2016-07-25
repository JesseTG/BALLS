#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T22:55:59
#
#-------------------------------------------------
include(../../common.pri)

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
  ../../BALLS \
  ../../QPropertyEditor

LIBS += \
  -L$$top_builddir/QPropertyEditor \
  -lQPropertyEditor

OBJECTS += \
  ../../BALLS/$${OBJECTS_DIR}/Vector2Property.o \
  ../../BALLS/$${OBJECTS_DIR}/moc_Vector2Property.o \
  ../../BALLS/$${OBJECTS_DIR}/Vector3Property.o \
  ../../BALLS/$${OBJECTS_DIR}/moc_Vector3Property.o \
  ../../BALLS/$${OBJECTS_DIR}/Vector4Property.o \
  ../../BALLS/$${OBJECTS_DIR}/moc_Vector4Property.o \
  ../../BALLS/$${OBJECTS_DIR}/VectorProperty.o \
  ../../BALLS/$${OBJECTS_DIR}/MatrixProperty.o \
  ../../BALLS/$${OBJECTS_DIR}/MatrixProperties.o \
  ../../BALLS/$${OBJECTS_DIR}/moc_MatrixProperties.o \
  ../../BALLS/$${OBJECTS_DIR}/TypeInfo.o \
  ../../BALLS/$${OBJECTS_DIR}/Constants.o \
  ../../BALLS/$${OBJECTS_DIR}/precompiled.o \
  ../../BALLS/$${OBJECTS_DIR}/MetaTypeConverters.o \
