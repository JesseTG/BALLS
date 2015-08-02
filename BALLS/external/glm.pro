TARGET = glm
TEMPLATE = aux

CONFIG += c++11

DEFINES += \
	GLM_META_PROG_HELPERS

HEADERS += \
	$$files(glm/glm/*.hpp, true)

SOURCES += \
	$$files(glm/glm/*.inl, true)
