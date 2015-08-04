# All dependencies have a .pro; clone them first!
#
# NOTE: You can add variables on the command line with the same syntax as here!
# i.e. BALLS+=spain
# Better document this for later

cache()

TEMPLATE = subdirs

SUBDIRS = \
		QPropertyEditor \
		glm \
		qtpropertybrowser \
		Qtilities \
		BALLS \
		BALLS-Tests

glm.file = glm.pro
glm.makefile = ""

qtpropertybrowser.subdir = qt-solutions/qtpropertybrowser

Qtilities.file = Qtilities/src/Qtilities.pro
Qtilities.depends = qtpropertybrowser

BALLS.depends = glm qtpropertybrowser Qtilities

BALLS-Tests.depends = glm

lessThan(QT_MAJOR_VERSION, 5) {
	error("Qt 5 is required, but only $${QT_VERSION} is available")
}
