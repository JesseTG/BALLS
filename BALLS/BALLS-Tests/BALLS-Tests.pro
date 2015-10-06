include(../common.pri)

TEMPLATE = subdirs
CONFIG += testcase console c++14

SUBDIRS += \
		TestConversions \
		TestJSONConversions \
		TestUniforms \
		PropertyObjectTests \

DEFINES += GLM_META_PROG_HELPERS
