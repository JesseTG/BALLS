TEMPLATE = subdirs
CONFIG += testcase console c++14

SUBDIRS += \
		TestConversions \
		TestJSONConversions

DEFINES += GLM_META_PROG_HELPERS
OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp
