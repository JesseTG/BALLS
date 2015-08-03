CONFIG += c++11
TARGET = Qtilities
TEMPLATE = subdirs
OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp
QTILITIES = core coregui
DEFINES += QTILITIES_PROPERTY_BROWSER

message(Qtilities: $$CONFIG)
SUBDIRS = Qtilities/src/Qtilities.pro
