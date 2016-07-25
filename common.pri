CONFIG(debug, debug|release) {
  BUILD_TYPE = debug
}
else:CONFIG(release, debug|release) {
  BUILD_TYPE = release
}
else {
  warning("Unknown build type; defaulting to debug")
  BUILD_TYPE = debug
}

DEFINES += \
  GLM_META_PROG_HELPERS \
  GENERATOR_USE_GLM \

OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp

#QT += KIOCore KIOFileWidgets KIOWidgets KNTLM

INCLUDEPATH *= \
  $$MOC_DIR \
  $$UI_DIR \
  $$RCC_DIR \
  /usr/include \
  /usr/local/include \
  /usr/include/x86_64-linux-gnu \
  /usr/include/x86_64-linux-gnu/qt5 \
  /usr/include/qt5 \
  /usr/include/KF5/KIOCore \
  /usr/include/KF5/KIOFileWidgets \

DESTDIR = $$PWD/../build/$${BUILD_TYPE}-$${QMAKE_CC}/dist

LIBS *= \
  -L/usr/lib \
  -L/usr/local/lib \
  -L/usr/lib/x86_64-linux-gnu \

