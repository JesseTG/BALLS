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

DESTDIR = $$clean_path($$PWD/../build/$${BUILD_TYPE}/dist)
