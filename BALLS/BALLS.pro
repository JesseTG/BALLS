CONFIG += qt c++14

TEMPLATE = subdirs

SUBDIRS = \
		QPropertyEditor \
		BALLS \
		BALLS-Tests \
		$$files(external/*.pro, false)
