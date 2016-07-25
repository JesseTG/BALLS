include($$top_srcdir/common.pri)

TEMPLATE = subdirs
CONFIG += testcase console c++14

SUBDIRS += \
  TestConversions \
  TestJSONConversions \
  TestUniforms \
  PropertyObjectTests \
