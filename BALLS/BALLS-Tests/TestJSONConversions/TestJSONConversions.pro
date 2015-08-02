#-------------------------------------------------
#
# Project created by QtCreator 2015-07-26T13:16:53
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = tst_TestJSONConversionsTest
CONFIG   += console testcase c++14
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += GLM_META_PROG_HELPERS
OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp

INCLUDEPATH += ../../BALLS

SOURCES += tst_TestJSONConversionsTest.cpp \
	../../BALLS/util/MetaTypeConverters.cpp \
	../../BALLS/precompiled.cpp
