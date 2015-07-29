TEMPLATE = subdirs
CONFIG += testcase console c++14

SUBDIRS += \
		TestConversions \
		TestJSONConversions

DEFINES += GLM_META_PROG_HELPERS
