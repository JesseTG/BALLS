#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T18:50:12
#
#-------------------------------------------------

include(../../common.pri)

QT       += widgets testlib

TARGET = tst_TestConversions
CONFIG   += testcase console c++14
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../BALLS
SOURCES += tst_TestConversions.cpp \
	../../BALLS/util/MetaTypeConverters.cpp \
	../../BALLS/precompiled.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\" \
	GLM_META_PROG_HELPERS
