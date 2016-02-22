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

OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp

INCLUDEPATH *= \
  $$MOC_DIR \
  $$UI_DIR \
  $$RCC_DIR \
  /usr/include \
  /usr/local/include \
  /usr/include/x86_64-linux-gnu \
  /usr/include/x86_64-linux-gnu/qt5 \
  /usr/include/qt5 \

DESTDIR = $$PWD/../build/$${BUILD_TYPE}-$${QMAKE_CC}/dist

LIBS *= \
  -L/usr/lib \
  -L/usr/local/lib \
  -L/usr/local/clang-3.5.0/lib \
  -L/usr/local/clang-3.6.0/lib \
  -L/usr/local/clang-3.7.0/lib \
  -L/usr/local/clang-3.8.0/lib \
  -L/usr/lib/x86_64-linux-gnu

