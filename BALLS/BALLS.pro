# All dependencies have a .pro; clone them first!
#
# NOTE: You can add variables on the command line with the same syntax as here!
# i.e. BALLS+=spain
# Better document this for later

TEMPLATE = subdirs

SUBDIRS = \
	QPropertyEditor \
	Qtilities \
	BALLS \
	BALLS-Tests

QTILITIES = core coregui

Qtilities.file = Qtilities/src/Qtilities.pro

BALLS.depends = Qtilities QPropertyEditor

BALLS-Tests.depends = BALLS

lessThan(QT_MAJOR_VERSION, 5) {
	error("Qt 5 is required, but only $${QT_VERSION} is available")
}
