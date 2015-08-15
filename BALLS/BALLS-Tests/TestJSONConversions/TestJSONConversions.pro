#-------------------------------------------------
#
# Project created by QtCreator 2015-07-26T13:16:53
#
#-------------------------------------------------

include(../../common.pri)

QT       += testlib
QT       -= gui

TARGET = tst_TestJSONConversionsTest
CONFIG   += console testcase c++14
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += GLM_META_PROG_HELPERS

INCLUDEPATH += ../../BALLS

SOURCES += tst_TestJSONConversionsTest.cpp \
	../../BALLS/util/MetaTypeConverters.cpp \
	../../BALLS/precompiled.cpp
