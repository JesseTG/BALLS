#-------------------------------------------------
#
# Project created by QtCreator 2015-09-17T13:48:57
#
#-------------------------------------------------

include(../../common.pri)

QT       += core gui widgets testlib

TARGET = tst_TestUniformsTest
CONFIG   += console testcase c++14
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += GLM_META_PROG_HELPERS

INCLUDEPATH += \
  ../../BALLS \
  ../../QPropertyEditor

SOURCES += \
  tst_TestUniformsTest.cpp \

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
  ../../BALLS/$${OBJECTS_DIR}/Uniforms.o \
  ../../BALLS/$${OBJECTS_DIR}/AABB.o \
  ../../BALLS/$${OBJECTS_DIR}/ArcBall.o \
  ../../BALLS/$${OBJECTS_DIR}/ArcLookAt.o \
  ../../BALLS/$${OBJECTS_DIR}/moc_Uniforms.o \
  ../../BALLS/$${OBJECTS_DIR}/Logging.o \
  ../../BALLS/$${OBJECTS_DIR}/TypeInfo.o \
  ../../BALLS/$${OBJECTS_DIR}/Constants.o \
  ../../BALLS/$${OBJECTS_DIR}/precompiled.o \
  ../../BALLS/$${OBJECTS_DIR}/MetaTypeConverters.o
