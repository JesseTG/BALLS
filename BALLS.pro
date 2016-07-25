# All dependencies have a .pro; clone them first!
#
# NOTE: You can add variables on the command line with the same syntax as here!
# i.e. BALLS+=spain
# Better document this for later

TEMPLATE = subdirs
CONFIG += c++14
SUBDIRS = \
  QPropertyEditor \
  BALLS \
  BALLS-Tests

OTHER_FILES += \
  .clang-format \
  CONTRIBUTING.md \
  .gitignore \
  .qmake.conf \
  travis/clone.sh \
  travis/makeit.sh \
  .travis.yml \

DISTFILES += \
  LICENSE \
  README.md \

BALLS.depends = QPropertyEditor

BALLS-Tests.depends = BALLS

lessThan(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 5) {
  error("Qt 5.5 is required, but only $${QT_VERSION} is available")
}

message(CONFIG: $$CONFIG)
message(Qt version: $$QT_VERSION)
message(Compiler: $$QMAKE_CC/$$QMAKE_CXX)
message($$system($$QMAKE_CXX --version))
