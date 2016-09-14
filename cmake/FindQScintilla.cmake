# - Try to find the QScintilla2 includes and library
# which defines
#
# QSCINTILLA_FOUND - system has QScintilla2
# QSCINTILLA_INCLUDE_DIR - where to find qextscintilla.h
# QSCINTILLA_LIBRARIES - the libraries to link against to use QScintilla
# QSCINTILLA_LIBRARY - where to find the QScintilla library (not for general use)

# copyright (c) 2007 Thomas Moenicke thomas.moenicke@kdemail.net
# Heavily based on https://git.io/viwyp
#
# Redistribution and use is allowed according to the terms of the FreeBSD license.

find_path(QSCINTILLA_INCLUDE_DIR
  NAMES Qsci qsciglobal.h
  PATHS "${Qt5Core_INCLUDE_DIRS}" /usr/include/x86_64-linux-gnu/qt5
  PATH_SUFFIXES Qsci
)

find_library(QSCINTILLA_LIBRARY
  NAMES qt5scintilla2 libqt5scintilla2
  PATHS ${Qt5Core_LIBRARIES}
)

include(FindPackageHandleStandardArgs)

message(STATUS ${QSCINTILLA_INCLUDE_DIR})
message(STATUS ${QSCINTILLA_LIBRARY})

find_package_handle_standard_args(
  QScintilla
  FOUND_VAR QSCINTILLA_FOUND
  REQUIRED_VARS QSCINTILLA_INCLUDE_DIR QSCINTILLA_LIBRARY
  VERSION_VAR QSCINTILLA_VERSION
)

message(STATUS ${QSCINTILLA_VERSION})

set(QSCINTILLA_LIBRARIES ${QSCINTILLA_LIBRARY})
set(QSCINTILLA_INCLUDE_DIRS ${QSCINTILLA_INCLUDE_DIR})

mark_as_advanced(QSCINTILLA_INCLUDE_DIR QSCINTILLA_LIBRARY)