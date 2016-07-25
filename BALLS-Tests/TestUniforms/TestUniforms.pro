include($$top_srcdir/common.pri)

QT       += core gui widgets testlib

TARGET = tst_TestUniformsTest
CONFIG   += console testcase c++14
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += GLM_META_PROG_HELPERS

INCLUDEPATH += \
  $$top_srcdir/BALLS \
  $$top_srcdir/QPropertyEditor \
# BALLS must come first in this list (because of multiple precompiled.hpp's)

SOURCES += \
  tst_TestUniformsTest.cpp \

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
  $$top_builddir/BALLS/$${OBJECTS_DIR}/Uniforms.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/AABB.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/ArcBall.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/ArcLookAt.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/moc_Uniforms.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/Logging.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/TypeInfo.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/Constants.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/precompiled.o \
  $$top_builddir/BALLS/$${OBJECTS_DIR}/MetaTypeConverters.o
