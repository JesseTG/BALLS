# All dependencies have a .pro; clone them first!
#
# NOTE: You can add variables on the command line with the same syntax as here!
# i.e. BALLS+=spain
# Better document this for later

CONFIG += qt c++14

TEMPLATE = subdirs

SUBDIRS = \
		QPropertyEditor \
		BALLS \
		BALLS-Tests \
		$$files(external/*.pro, false)
