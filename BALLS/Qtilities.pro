include(common.pri)

CONFIG += c++11
TARGET = Qtilities
TEMPLATE = subdirs

QTILITIES = core coregui
DEFINES += QTILITIES_PROPERTY_BROWSER

SUBDIRS = Qtilities/src/Qtilities.pro
